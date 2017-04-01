# template cmd
echo abc
2>&- export VAR=value || setenv VAR value
echo def
pwd
echo ghi
echo 'zut' > /tmp/history_cat_file
cat -e /tmp/history_cat_file
rm -f /tmp/history_cat_file

!e
!ech
!echo d
echo !p !c

!'r'
!"r"
!\r

!'r'm
!"r"m
!\r\m

!'2'
!2>
