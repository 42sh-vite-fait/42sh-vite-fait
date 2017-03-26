mkdir -p /tmp/test_builtin_cd_folder
2>/dev/null export CDPATH=/tmp || setenv CDPATH /tmp
cd /
pwd
cd test_builtin_cd_folder
pwd
