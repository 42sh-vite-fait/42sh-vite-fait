cat << EOF | /tmp/bin/42sh
echo abc | wc
echo 123 | cat -e | cat -e | cat -e
env | grep USER
EOF
