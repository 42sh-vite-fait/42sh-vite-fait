${FTSH_PATH} -c 'echo ---
cat /tmp/crash_file'

# output different si un espace est devant le 'echo'
${FTSH_PATH} -c ' echo ---
cat /tmp/crash_file'
