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
cp -f `which bash` /tmp/bin/bash

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
	#   input_file:   simple_command/ls_basic/input.sh
    test_suite=$1
    test_case=$2
    test_case_path="$TESTS_ROOT/$test_suite/$test_case"
    input_file=$test_case_path/input.sh

	valgrind /tmp/bin/42sh -c "$(cat ${input_file})"
    status=$?
    if [ $status -ne 0 ]; then
        echo $status
        exit ;
    fi
}

/usr/bin/printf "============================ START LEAKS TESTS ==========================\n"
for TEST_SUITE in $TESTS_ROOT/*; do
	if [ -d "${TEST_SUITE}" ] && test "$(basename ${TEST_SUITE})" != 'do_not_test'; then
        for TEST_CASE in $TEST_SUITE/*; do
            if [ -d "${TEST_CASE}" ]; then
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
