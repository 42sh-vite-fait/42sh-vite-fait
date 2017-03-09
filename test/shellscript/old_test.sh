#!/usr/bin/env mksh

set -e

FTSH_PATH='./42sh'
TEST_DEBUG_PATH="$(pwd)/test/debug_out"

cleanup() {
	rm -f cmd.{err,out}
}

trap cleanup EXIT

# $1 = Module (ast, lexer, input)
# $2 = Nom du test
shell_test() {
	testcase_path="${TEST_DEBUG_PATH}/$1/$2"
	echo "${testcase_path}"
	command_content=$(cat ${testcase_path}.cmd; printf xxx)
	command_content=${command_content%xxx}
	${FTSH_PATH} -d $1 -c "${command_content}" > cmd.out 2> cmd.err || true
	command diff --suppress-common-lines --minimal cmd.out ${testcase_path}.out
	command diff --suppress-common-lines --minimal cmd.err ${testcase_path}.err
}

# $1 = Folder (ast, lexer, input)
call_test_on_each_files() {
	filenames=$(find "${TEST_DEBUG_PATH}/$1" -type f -name "*.cmd" | xargs basename -s '.cmd')
	for testcase in $filenames;
	do
		shell_test $1 ${testcase};
	done
}

for module in ${TEST_DEBUG_PATH}/*;
do
	if [ -d ${module} ];
	then
		call_test_on_each_files $(basename ${module})
	fi
done

echo 'All tests passed!'
