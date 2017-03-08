#!/bin/sh

C_CYAN="\033[36;1m"
C_GREEN="\033[32;1m"
C_RED="\033[31;1m"
C_CLEAR="\033[0m"

RENDU_PATH="`pwd`"
TESTS_ROOT="$RENDU_PATH/test/yyang_bash_tests"

exit_status=0
count_success=0
count_failure=0

mkdir -p /tmp/bin
cp $RENDU_PATH/42sh /tmp/bin/
cp -f `which mksh` /tmp/bin/mksh

if [ "$?" -ne "0" ]; then
    exit 1
fi

print_result ()
{
    if [ $1 -eq 0 ]
    then
        /usr/bin/printf $C_GREEN"$2"$C_CLEAR
        count_success=$((count_success+1))
    else
        /usr/bin/printf $C_RED"$2"$C_CLEAR
        count_failure=$((count_failure+1))
        exit_status=1
    fi
    /usr/bin/printf " "
}

diff_test ()
{
	#   Suite:        simple_command
	#   Case:         ls_basic
	#   Case_path:    simple_command/ls_basic
	#   Input_file:   simple_command/ls_basic/input.sh
    test_suite=$1
    test_case=$2
    test_case_path="$TESTS_ROOT/$test_suite/$test_case"
    input_file=$test_case_path/input.sh

    test_case_tmp="$test_case_path/.tmp"
    rm -rf $test_case_tmp 2>&1 >/dev/null
    mkdir -p $test_case_tmp

	# 42sh
    test_case_tmp_ftsh_stdout="$test_case_tmp/actual_stdout"
    test_case_tmp_ftsh_stderr="$test_case_tmp/actual_stderr"
    test_case_tmp_ftsh_exit_status="$test_case_tmp/actual_exit_status"
	# echo "========> $test_case_tmp_ftsh_stdout <++++++"
	# echo "========> $test_case_tmp_ftsh_stderr <++++++"
	# echo "========> $test_case_tmp_ftsh_exit_status <++++++"
    /tmp/bin/42sh < ${input_file} > $test_case_tmp_ftsh_stdout 2> $test_case_tmp_ftsh_stderr
    echo "exit_code: $?" > $test_case_tmp_ftsh_exit_status

	# mksh
    test_case_tmp_mksh_stdout="$test_case_tmp/expected_stdout"
    test_case_tmp_mksh_stderr="$test_case_tmp/expected_stderr"
    test_case_tmp_mksh_exit_status="$test_case_tmp/expected_exit_status"
	# echo "========> $test_case_tmp_mksh_stdout <++++++"
	# echo "========> $test_case_tmp_mksh_stderr <++++++"
	# echo "========> $test_case_tmp_mksh_exit_status <++++++"
    /tmp/bin/mksh < ${input_file} > $test_case_tmp_mksh_stdout 2> $test_case_tmp_mksh_stderr
    echo "exit_code: $?" >> $test_case_tmp_mksh_exit_status

	# Selection de la sortie voulu
    if [ -f $test_case_path/expected_stdout ]; then
        expected_stdout_file=$test_case_path/expected_stdout
    else
        expected_stdout_file=$test_case_tmp_mksh_stdout
    fi
    if [ -f $test_case_path/expected_stderr ]; then
        expected_stderr_file=$test_case_path/expected_stderr
    else
        expected_stderr_file=$test_case_tmp_mksh_stderr
    fi
	expected_exit_status_file=$test_case_tmp_mksh_exit_status

	# Diff stdout
    diff $expected_stdout_file $test_case_tmp_ftsh_stdout
    print_result "$?" stdout

	# Diff stderr
    diff $expected_stderr_file $test_case_tmp_ftsh_stderr
    print_result "$?" stderr

	# Diff exit status
    diff $expected_exit_status_file $test_case_tmp_ftsh_exit_status
    print_result "$?" exit_status

    echo "$test_suite/$test_case/input.sh"
}

/usr/bin/printf "============================ START DIFF TESTS ==========================\n"
for TEST_SUITE in $TESTS_ROOT/*; do
	if [ -d "${TEST_SUITE}" ] && [[ "${TEST_SUITE}" != *_NOLOAD ]]; then
        for TEST_CASE in $TEST_SUITE/*; do
            if [ -d "${TEST_CASE}" ] && [[ "${TEST_CASE}" != *_NOLOAD ]]; then
                diff_test `basename $TEST_SUITE` `basename $TEST_CASE`
            fi
        done
    fi
done

if [ $count_failure -gt 0 ]; then
    echo "$C_RED\c"
else
    echo "$C_GREEN\c"
fi
echo "============================ $count_failure failed, $count_success passed ============================"
echo "$C_CLEAR\c"
echo "Thx to yyang42/42sh_posix for the tests suites :)"

exit $exit_status
