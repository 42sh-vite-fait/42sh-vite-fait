echo "Single Quote"
echo 'foo
bar'
echo 'foo
bar'
echo 'foo\
bar'

echo "Double Quote"
echo "foo
bar"
echo "foo
bar"
echo "foo\
bar" 

echo "Double Quote Single Quote"
echo "echo 'foo
bar'"
echo "echo 'foo
bar'"
echo "echo 'foo\
bar'"
echo '\'abcd\''
echo "\'abcd\'"
echo "\\'abcd\\'"
echo 'uvwx'
echo -en "\01" | cat -v
echo "'"
echo \'
echo "$'\''"
echo $'\''
echo $'\'abcd\''
echo "$'\'abcd\''"
echo ${v/1/\'}
echo ${v/\'/2}
echo 'ab\x{}cd'
echo 'ab\x{41}cd'
echo 'ab\x41cd'
echo 'ab\x{4}cd'
echo 'ab\x4cd'
echo 'ab\x{cde'
echo 'ab\x{cde'
echo 'ab\x{cd}e'
echo 'ab\x{c}de'
echo '\x{abcX'
echo '\x{ab}cX'
echo '\x{}X'
echo '\x{X'
echo '\x{01234567X'
echo '\x{41}b'
echo '\x{}bc'
echo '\x{1}bcd'
echo '\x{bde'
echo 1 -- 2 -- 3
# why does this work, this list was born of frustration, I tried
# everything I could think of.
echo \'{test//"'"/\'\\\'\'}\'" "
echo "'{test//"'"/}'"
echo "'{test//"'"/"'\\''"}'"
echo "'{test//"'"/\'\\'\'}'"
echo "'{test//'/}'"
echo "'{test//"'"/'\\''}'" # hangs waiting for '
echo "{test//str/"dddd"}"
echo {test//str/"dddd"}
echo {test//str/"'"}
echo "{test//str/"'"}"
echo "{test//str/'}"   # hangs
echo "${test//"'"/"'"}"
