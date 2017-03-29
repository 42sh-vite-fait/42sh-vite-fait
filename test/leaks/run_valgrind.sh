run_valgrind() {
	valgrind \
		--show-leak-kinds=definite,indirect,possible \
		--leak-check=full \
		--suppressions=./test/leaks/valgrind.supp \
		./42sh < $1
}

# $1 SUITE
# $2 CASE

if [ $# -eq 2 ];
then
	run_valgrind "test/shellscript/$1/$2/input.sh"
else
	echo "$0 SUITE CASE"
fi
