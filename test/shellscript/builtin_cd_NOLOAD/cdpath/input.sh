mkdir -p /tmp/test_builtin_cd_folder
setenv CDPATH /tmp
cd /
pwd
cd test_builtin_cd_folder
pwd

unsetenv CDPATH
mkdir /tmp/bash-dir-a
setenv CDPATH .:/tmp
cd bash-dir-a
pwd
printenv PWD
rmdir  /tmp/bash-dir-a
