mkdir -p /tmp/test_binary_path
echo "echo abc" > /tmp/test_binary_path/myexec
chmod 755 /tmp/test_binary_path/myexec

echo "=======1"
myexec

echo "=======2"
2>/dev/null export PATH="/tmp/test_binary_path:/usr/bin:/bin" || setenv PATH "/tmp/test_binary_path:/usr/bin:/bin"
myexec

echo "=======3"
/tmp/test_binary_path/myexec

echo "=======4"
setenv PATH
myexec > /dev/null

echo "=======5"
unsetenv PATH
myexec > /dev/null

echo "=======6"
