## Special built-in utilities.
- Subject to any redirection.
- Shell may abort on syntax error.
- Variable assignments shall remain in effect after the special built-in completes

# break
- EXEC. takes UNSIGNED int as param (atoi wont work).

# colon
- EZ MONEY B*TCHE$

# continue
- EXEC. takes UNSIGNED int as param (atoi wont work).

# dot
- ?????? Same PATH searching function is required (as to find executables), but target file does not need to be executable.
- ENOF -> interactive ? abort : warn.
- May be interesting to mimic ksh that allows positionnal parameters. dot would then behave like a function (input ?).

# eval
- Similar to a one line lambda function once args are concatenated.

# exec
- Need more investigating...

# exit
- called from trap ? exit immediately : trap (then calls exit)

# export
- `export -p` => print all as an op that can be used by the shell to get back to the current environment.
- `export foobar` is a valid command.

# readonly
- set local readonly variable.
- overrides exported variables.
- cannot be overriden by any of set, export, etc...

# return
- view exit status

# set
- 

# shift
- n invalid or > $# -> interactive ? abort : warn.

# times
- output floats...

# trap
- trivial. Implies a handler function pointer map.

# unset
- environment.


## Regular built-in utilities

# pwd
- trivial

# alias
- EXEC

# fc
- only in interactive.
- HISTORY

# unalias
- EXEC

# bg
- JOB CONTROL

# fg
- JOB CONTROL

# jobs
- JOB CONTROL


# cd
- SHELL EXEC ENV

# getopts
- output only

# newgrp
- Need more investigating...

# read
- ENV.
- processed through field splitting/parameter expansion.
 
# umask
- Needs more investigating...
 
# wait
- JOB CONTROL
 


# command
- bypass function lookup. 
- ignore builtin special argument (treat it like it is a regular builtin).
- sysconf(3) to get default PATH.
- need to access alias map.
- need to search in PATH.

# kill
- JOB CONTROL


# false
- trivial

# true
- trivial


## 42 built-ins

# env
- trivial

# history
- ! and ^ is part of expansion if option is enabled.
- 

# setenv
- ???