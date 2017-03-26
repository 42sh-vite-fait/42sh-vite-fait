echo '()' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing 2> /tmp/subshell_err_parsing_msg
cat /tmp/subshell_err_parsing_msg

echo '(;)' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing 2> /tmp/subshell_err_parsing_msg
cat /tmp/subshell_err_parsing_msg

echo '(|)' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing 2> /tmp/subshell_err_parsing_msg
cat /tmp/subshell_err_parsing_msg

echo '(>)' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing 2> /tmp/subshell_err_parsing_msg
cat /tmp/subshell_err_parsing_msg

echo '(&&)' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing 2> /tmp/subshell_err_parsing_msg
cat /tmp/subshell_err_parsing_msg

echo '(echo a;)' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing 2> /tmp/subshell_err_parsing_msg
cat /tmp/subshell_err_parsing_msg

echo '(echo b &&)' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing 2> /tmp/subshell_err_parsing_msg
cat /tmp/subshell_err_parsing_msg

echo '(echo b && > /tmp/subshell_err_zut)' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing 2> /tmp/subshell_err_parsing_msg
cat /tmp/subshell_err_parsing_msg

echo '(echo c |)' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing 2> /tmp/subshell_err_parsing_msg
cat /tmp/subshell_err_parsing_msg

echo '(echo c | >> /tmp/subshell_err_zut)' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing 2> /tmp/subshell_err_parsing_msg
cat /tmp/subshell_err_parsing_msg

echo '(echo d; ())' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing 2> /tmp/subshell_err_parsing_msg
cat /tmp/subshell_err_parsing_msg

echo '(echo d; (echo d2;));' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing 2> /tmp/subshell_err_parsing_msg
cat /tmp/subshell_err_parsing_msg

echo '(;echo e)' > /tmp/subshell_err_parsing
/tmp/bin/42sh < /tmp/subshell_err_parsing 2> /tmp/subshell_err_parsing_msg
cat /tmp/subshell_err_parsing_msg
