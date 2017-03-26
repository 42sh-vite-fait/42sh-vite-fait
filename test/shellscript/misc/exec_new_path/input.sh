mkdir -p /tmp/test_binary_path
echo "echo abc" > /tmp/test_binary_path/myexec
chmod 755 /tmp/test_binary_path/myexec

# Fail
myexec

# Pass
setenv PATH "/tmp/test_binary_path:/usr/bin:/bin"
myexec

# Pass
/tmp/test_binary_path/myexec

# Fail
setenv PATH
myexec > /dev/null

# Fail
unsetenv PATH
myexec > /dev/null

# Fail
./test_binary_path/myexec

# Fail
cd /tmp/test_binary_path
myexec
