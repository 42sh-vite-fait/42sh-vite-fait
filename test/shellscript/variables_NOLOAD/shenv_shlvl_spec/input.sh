export SHLVL=4
env | grep SHLVL=
/tmp/bin/42sh -c 'env && /tmp/bin/42sh -c "env"' | grep SHLVL=
