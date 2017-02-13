tmp_name='temporary_dump'
dump_name='dump'
random_size=1024
ret=0
i=0
SIG_LIMIT=128

while true;
do
	echo ${i}
	cat /dev/random | head -c ${random_size} > ${tmp_name}
	cat ${tmp_name} | ./42sh
	if test $? -gt ${SIG_LIMIT};
	then
		mv ${tmp_name} "${dump_name}_${i}"
	fi
	i=$(( ${i} + 1 ))
done
