# template cmd
echo abc
2>&- export VAR=value || setenv VAR value
echo def
pwd
echo ghi
echo 'zut' > /tmp/history_cat_file
cat -e /tmp/history_cat_file
rm -f /tmp/history_cat_file

# basic use case
echo !-3
echo !3
!-3
!3

# overflow
echo !999999999999999999999999999
echo !-999999999999999999999999999
!999999999999999999999999999
!-999999999999999999999999999

# zero
echo !-0
echo !0
!-0
!0
