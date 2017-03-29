2>/dev/null unset PWD || unsetenv PWD
rm -rf toto
mkdir toto
cd toto
pwd
cd -- -

2>/dev/null PWD="tata" || setenv PWD "tata"
rm -rf toto
mkdir toto
cd toto
pwd
cd -- -
rm -rf toto

env -i ./42sh -c "cd . ; /bin/pwd ;"

2>&- cd tutu
cd /tmp
cd -
pwd
