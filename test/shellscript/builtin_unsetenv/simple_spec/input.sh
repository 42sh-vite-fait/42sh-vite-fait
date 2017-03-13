setenv globalvar 456
env | grep globalvar=
unsetenv globalvar
env | grep globalvar=
