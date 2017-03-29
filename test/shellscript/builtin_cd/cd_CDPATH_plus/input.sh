cd /tmp
rm -rf test01
mkdir -p test01/test02/test03

echo 0
cd /tmp
2>&- CDPATH=/tmp/test01 || setenv CDPATH /tmp/test01
cd test02

echo 1
cd /tmp
2>&- CDPATH=:test01 || setenv CDPATH :test01
cd test01
cd /tmp
cd test02

echo 2
cd /tmp
2>&- CDPATH=test01: || setenv CDPATH test01:
cd test01
cd /tmp
cd test02

echo 3
cd /tmp
2>&- CDPATH=: || setenv CDPATH :
cd test01

echo 4
cd /tmp
2>&- CDPATH=:: || setenv CDPATH ::
cd test01

echo 5
cd /tmp
2>&- CDPATH=test01/test02::test01 || setenv CDPATH test01/test02::test01
cd test01
cd /tmp
cd test02
cd /tmp
cd test03

echo 6
cd /tmp
rm -rf nosuchpath
2>&- CDPATH=nosuchpath::test01 || setenv CDPATH nosuchpath::test01
cd test01
cd /tmp
cd test02
cd /tmp

echo 7
cd /tmp
2>&- CDPATH=test01::nosuchpath || setenv CDPATH test01::nosuchpath
cd test01
cd /tmp
cd test02
cd /tmp

cd /tmp
rm -rf test01
