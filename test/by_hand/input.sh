launch_tests() {
echo -n "\x00" | ./42sh
echo -n "echo abc\x00echo def" | ./42sh # abcecho def
echo -n "" | ./42sh
echo -n "'" | ./42sh # no closing quote
echo -n "(" | ./42sh
echo -n "\"" | ./42sh

### -c
./42sh -c 'echo abc'
./42sh -c 'echo abc
def'
./42sh -c "" | ./42sh
./42sh -c "'" | ./42sh
./42sh -c "(" | ./42sh
./42sh -c "\"" | ./42sh

### priority to -c above stdin
./42sh -c 'echo abc | (cat -e | wc -l | cut -d " " -f 8)' <&-

### Commandes en input
echo "cat\nzut" | ./42sh

### Bad TERM variable
TERM= ./42sh
TERM=merde ./42sh
TERM=dumb ./42sh

### ulimit -n 10
mksh -c 'ulimit -n 10 && ./42sh'

### ulimit -n 16
mksh -c 'ulimit -n 16 && ./42sh'

### ulimit -n 17
mksh -c 'ulimit -n 17 && ./42sh -c "echo abc | (cat -e | cat -e); echo def"'
}

echo "===> Compile with Sanitize"
make re SAN=yes DEBUG=yes >/dev/null
echo "launch_tests"
launch_tests

echo "===> Compile for Leaks"
make re DEBUG=yes >/dev/null
echo "launch_tests"
export CHECK_LEAKS=yes
launch_tests
