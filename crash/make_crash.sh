filename='crash_file'
random_size=1024
ret=0
i=0

while test ${ret} -eq 0;
do
	echo ${i}
	cat /dev/random | head -c ${random_size} > ${filename}
	cat ${filename} | ./42sh -i
	ret=$?
	i=$(( ${i} + 1 ))
done
