echo 'useless commands'; first=$(ls -1 2>/dev/null | head -n 1); test -d ${first} && (touch ${first}/file && cat /dev/random | base64 | head -c 42) 2>&1 >output || mkdir ${first}
