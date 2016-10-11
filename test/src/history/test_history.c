#include "header.h"

extern t_history	g_history;

static void		test_00_history_contains(void)
{
	size_t		command_id;
	t_buffer	*cmd_ls = buffer_dup("ls -la");
	t_buffer	*cmd_echo = buffer_dup("echo hello");
	t_buffer	*cmd_kill = buffer_dup("kill -KILL 0");

	history_init(3);

	history_add(*cmd_ls);
	history_add(*cmd_echo);
	history_add(*cmd_kill);

	v_assert_int(true, ==, HIST_CONTAINS(g_history, 1));
	v_assert_int(true, ==, HIST_CONTAINS(g_history, 2));
	v_assert_int(true, ==, HIST_CONTAINS(g_history, 3));
	v_assert_int(false, ==, HIST_CONTAINS(g_history, 4));

	v_assert_str(cmd_ls->str, history_get(1)->str);
	v_assert_str(cmd_echo->str, history_get(2)->str);
	v_assert_str(cmd_kill->str, history_get(3)->str);
	v_assert_ptr(NULL, ==, history_get(4));

	free(cmd_ls);
	free(cmd_echo);
	free(cmd_kill);

	VTS;
}

static void		test_01_history_addFirstCommandId(void)
{
	t_buffer	command;
	size_t		command_id;

	history_init(10000);
	command = *buffer_init(&command, BUFFER_INIT_SIZE);

	command = *buffer_replace(&command, "ls -la");
	command_id = history_add(command);

	v_assert_size_t(1, ==, command_id);
	VTS;
}

static void		test_02_history_addManyCommandId(void)
{
	t_buffer	command;
	size_t		command_id;

	history_init(10000);
	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls -la");
	command_id = history_add(command);
	v_assert_size_t(1, ==, command_id);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls -la");
	command_id = history_add(command);
	v_assert_size_t(2, ==, command_id);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls -la");
	command_id = history_add(command);
	v_assert_size_t(3, ==, command_id);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls -la");
	command_id = history_add(command);
	v_assert_size_t(4, ==, command_id);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls -la");
	command_id = history_add(command);
	v_assert_size_t(5, ==, command_id);

	VTS;
}

static void		test_03_history_FindPattern(void)
{
	t_buffer	command;
	t_result	result;
	size_t		command_id;
	bool		found;

	history_init(2);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls -la");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls -la");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls -la");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "kill -KILL 0");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "echo kiki");
	command_id = history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "fc -l");
	history_add(command);

	found = history_find(&result, "kiki");
	v_assert_int(true, ==, found);
	v_assert_size_t(command_id, ==, result.command_id);
	v_assert_size_t(5, ==, result.offset);
	VTS;
}

static void		test_04_history_FindDontFind(void)
{
	t_buffer	command;
	t_result	result;
	bool		found;

	history_init(5);
	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls -la");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls -la");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls -la");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls -la");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls -la");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls -la");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "kill -KILL 0");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "echo kikou");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "fc -l");
	history_add(command);

	found = history_find(&result, "kiki");
	v_assert_int(false, ==, found);
	VTS;
}

static void		test_05_history_FindFrom(void)
{
	t_result	result;
	t_buffer	command;
	size_t		cmd_ls_tmp_id;
	size_t		cmd_echo_kiki_id;
	bool		found;

	history_init(5);
	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls -la");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls -la");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls -la");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls /tmp/kiki");
	cmd_ls_tmp_id = history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls -la");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "kill -KILL 0");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "echo kiki kiki");
	cmd_echo_kiki_id = history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "fc -l");
	history_add(command);

	found = history_find(&result, "kiki");
	v_assert_int(true, ==, found);
	v_assert_size_t(cmd_echo_kiki_id, ==, result.command_id);
	v_assert_size_t(10, ==, result.offset);

	found = history_find_from(&result, "kiki", result);
	v_assert_int(true, ==, found);
	v_assert_size_t(cmd_echo_kiki_id, ==, result.command_id);
	v_assert_size_t(5, ==, result.offset);

	found = history_find_from(&result, "kiki", result);
	v_assert_int(true, ==, found);
	v_assert_size_t(cmd_ls_tmp_id, ==, result.command_id);
	v_assert_size_t(8, ==, result.offset);

	found = history_find_from(&result, "kiki", result);
	v_assert_int(false, ==, found);

	VTS;
}

static void		test_06_history_FindStartWith(void)
{
	t_result	result;
	t_buffer	command;
	size_t		cmd_id;
	bool		found;

	history_init(10000);
	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls -la");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "rg ripgrep /");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls -laR /");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "rm -rf ~/* ~/.*");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ssh root@127.0.0.1");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "emacs hello");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "kill -KILL 0");
	cmd_id = history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "echo kikou");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "fc -l");
	history_add(command);

	found = history_find_start_with(&result, "kill");
	v_assert_int(true, ==, found);
	v_assert_size_t(cmd_id, ==, result.command_id);
	v_assert_size_t(0, ==, result.offset);
	VTS;
}

static void		test_07_history_FindStartWithNotFound(void)
{
	t_buffer	command;
	t_result	result;
	bool		found;

	history_init(10000);
	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls -la");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "rg ripgrep /");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls -laR /");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "rm -rf ~/* ~/.*");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ssh root@127.0.0.1");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "emacs hello");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "kill -KILL 0");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "echo kikou");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "fc -l");
	history_add(command);

	found = history_find_start_with(&result, "kikou");
	v_assert_int(false, ==, found);
	VTS;
}

#define BUFF_SIZE (4096)

static char		*read_all(const char *path)
{
	char		read_buff[BUFF_SIZE];
	t_buffer	buffer;
	ssize_t		ret;
	int			fd;

	fd = open(path, O_RDONLY);

	buffer_init(&buffer, BUFF_SIZE);
	while ((ret = read(fd, read_buff, BUFF_SIZE)) == BUFF_SIZE)
	{
		buffer_insert(&buffer, buffer.len, read_buff, ret);
	}
	buffer_insert(&buffer, buffer.len, read_buff, ret);

	close(fd);
	return (buffer.str);
}

#define HISTFILE ("/tmp/hist.test")

static void		test_08_history_SaveIntoFile(void)
{
	t_buffer	command;
	int			ret;

	history_init(10000);
	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls -la");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "rg ripgrep /");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ls -laR /");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "rm -rf ~/* ~/.*");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "ssh root@127.0.0.1");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "emacs hello\nca\nva");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "kill -KILL 0");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "echo kikou\nles\npotos");
	history_add(command);

	command = *buffer_init(&command, BUFFER_INIT_SIZE);
	command = *buffer_replace(&command, "echo \\\\");
	history_add(command);

	ret = history_save_into_file(HISTFILE);
	v_assert_int(0, ==, ret);

	const char *file_content = "echo \\\\\n\
echo kikou\\\n\
les\\\n\
potos\n\
kill -KILL 0\n\
emacs hello\\\n\
ca\\\n\
va\n\
ssh root@127.0.0.1\n\
rm -rf ~/* ~/.*\n\
ls -laR /\n\
rg ripgrep /\n\
ls -la\n";

	v_assert_str(file_content, read_all(HISTFILE));

	VTS;
}

static void		test_09_history_ReadFromFile(void)
{
	int			ret;

	history_init(10000);

	ret = history_load_from_file(HISTFILE);
	v_assert_int(0, ==, ret);

	v_assert_str("echo \\\\", history_get(1)->str);
	v_assert_str("echo kikou\nles\npotos", history_get(2)->str);
	v_assert_str("kill -KILL 0", history_get(3)->str);
	v_assert_str("emacs hello\nca\nva", history_get(4)->str);
	v_assert_str("ssh root@127.0.0.1", history_get(5)->str);
	v_assert_str("rm -rf ~/* ~/.*", history_get(6)->str);
	v_assert_str("ls -laR /", history_get(7)->str);
	v_assert_str("rg ripgrep /", history_get(8)->str);
	v_assert_str("ls -la", history_get(9)->str);

	VTS;
}

void			suite_history(void)
{
	test_00_history_contains();
	test_01_history_addFirstCommandId();
	test_02_history_addManyCommandId();

	test_03_history_FindPattern();
	test_04_history_FindDontFind();
	test_05_history_FindFrom();

	test_06_history_FindStartWith();
	test_07_history_FindStartWithNotFound();

	test_08_history_SaveIntoFile();
	test_09_history_ReadFromFile();

	VSS;
}
