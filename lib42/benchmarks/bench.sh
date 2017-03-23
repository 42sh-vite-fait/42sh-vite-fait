echo 'Flag: -O0'
make DEBUG=yes re > /dev/null
clang -I inc/ benchmarks/memset-test.c lib42.a && ./a.out
echo ''
echo 'Flag: -O2'
make PROD=yes re > /dev/null
clang -I inc/ benchmarks/memset-test.c lib42.a && ./a.out
