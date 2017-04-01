# template cmd
echo abc
2>&- export VAR=value || setenv VAR value
echo def
pwd
echo ghi
echo 'zut' > /tmp/history_cat_file
cat -e /tmp/history_cat_file
rm -f /tmp/history_cat_file

# simple quoted bang
echo === 1
echo '!!'

echo === 1.1
echo '!''!'

echo === 1.2
echo '!'!

echo === 1.3
echo !'!'

# backslashed bang
echo === 2
echo \!\!

echo === 2.1
echo \!!

echo === 2.2
echo !\!

echo === 2.3
echo !!\a

echo === 2.4
echo \a!!

# bash tests
echo '!'
echo "!"
echo !
echo "\!"
echo "!!"
echo " !!"
echo "!! "
echo "! !"
echo '!'
echo "!"
echo !
echo "\!"
echo '!' "!"
echo "'!'"
echo "!""!"
echo '!!'
