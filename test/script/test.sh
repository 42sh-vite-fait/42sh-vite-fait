#!/usr/bin/env bash

set -e

export FTSH_PATH='../../42sh'

cleanup() {
	rm -f cmd.{err,out}
}

trap cleanup EXIT

# $1 = Module (ast, lexer, input)
# $2 = Nom du test
shell_test() {
	test_name="$1/$2"
	echo "${test_name}"
	command_content=$(cat ${test_name}.cmd; printf xxx); command_content=${command_content%xxx}
	${FTSH_PATH} -d $1 -c "${command_content}" > cmd.out 2> cmd.err || true
	command diff --suppress-common-lines --minimal cmd.out ${test_name}.out
	command diff --suppress-common-lines --minimal cmd.err ${test_name}.err
}

# $1 = Folder (ast, lexer, input)
call_test_on_each_files() {
	filenames=$(find $1 -type f -name "*.cmd" | xargs basename -s '.cmd')
	while IFS= read -r line;
	do 
		shell_test $1 ${line};
	done <<< "${filenames}"
}

dir_test=$(find . ! -path . -type d)
while IFS= read -r folder;
do
	call_test_on_each_files $(basename ${folder});
done <<< "${dir_test}"

echo 'All tests passed!'
