# template cmd
echo abc
2>&- export VAR=value || setenv VAR value
echo def
pwd
echo ghi
echo 'zut' > /tmp/history_cat_file
cat -e /tmp/history_cat_file
rm -f /tmp/history_cat_file

echo bang
!e !p !2 !-1 !!

# no space in between
echo bang
!e!p!2!-1!!
