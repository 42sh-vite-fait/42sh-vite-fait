cat << EOF | /tmp/bin/42sh
echo abc | wc
echo 123 | cat -e | cat -e | cat -e
export MYVAR=ABC
env | grep MYVAR=
EOF
