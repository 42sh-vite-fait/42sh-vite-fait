#include "header.h"

extern t_history	g_history;

static void		test_00_history_contains(void)
{
	size_t		command_id;
	const char	*cmd_ls = strdup("ls -la");
	const char	*cmd_echo = strdup("echo hello");
	const char	*cmd_kill = strdup("kill -KILL 0");

	history_init(3);

	history_push(cmd_ls);
	history_push(cmd_echo);
	history_push(cmd_kill);

	v_assert_int(true, ==, HIST_CONTAINS(g_history, 1));
	v_assert_int(true, ==, HIST_CONTAINS(g_history, 2));
	v_assert_int(true, ==, HIST_CONTAINS(g_history, 3));
	v_assert_int(false, ==, HIST_CONTAINS(g_history, 4));

	v_assert_str(cmd_ls, history_get_id(1));
	v_assert_str(cmd_echo, history_get_id(2));
	v_assert_str(cmd_kill, history_get_id(3));
	v_assert_ptr(NULL, ==, history_get_id(4));
	VTS;
}

static void		test_01_history_pushFirstCommandId(void)
{
	size_t		command_id;

	history_init(10000);

	command_id = history_push(strdup("ls -la"));

	v_assert_size_t(1, ==, command_id);
	VTS;
}

static void		test_02_history_pushManyCommandId(void)
{
	size_t		command_id;

	history_init(10000);

	command_id = history_push(strdup("ls -la"));
	v_assert_size_t(1, ==, command_id);

	command_id = history_push(strdup("ls -la"));
	v_assert_size_t(2, ==, command_id);

	command_id = history_push(strdup("ls -la"));
	v_assert_size_t(3, ==, command_id);

	command_id = history_push(strdup("ls -la"));
	v_assert_size_t(4, ==, command_id);

	command_id = history_push(strdup("ls -la"));
	v_assert_size_t(5, ==, command_id);

	VTS;
}

static void		test_03_history_FindPattern(void)
{
	t_result	result;
	size_t		command_id;
	bool		found;

	history_init(2);

	history_push(strdup("ls -la"));
	history_push(strdup("ls -la"));
	history_push(strdup("ls -la"));
	history_push(strdup("kill -KILL 0"));
	command_id = history_push(strdup("echo kiki"));
	history_push(strdup("fc -l"));

	found = history_find(&result, "kiki");
	v_assert_int(true, ==, found);
	v_assert_size_t(command_id, ==, result.command_id);
	v_assert_size_t(5, ==, result.offset);
	VTS;
}

static void		test_04_history_FindDontFind(void)
{
	t_result	result;
	bool		found;

	history_init(5);

	history_push(strdup("ls -la"));
	history_push(strdup("ls -la"));
	history_push(strdup("ls -la"));
	history_push(strdup("ls -la"));
	history_push(strdup("ls -la"));
	history_push(strdup("ls -la"));
	history_push(strdup("kill -KILL 0"));
	history_push(strdup("echo kikou"));
	history_push(strdup("fc -l"));

	found = history_find(&result, "kiki");
	v_assert_int(false, ==, found);
	VTS;
}

static void		test_05_history_FindFrom(void)
{
	t_result	result;
	size_t		cmd_ls_tmp_id;
	size_t		cmd_echo_kiki_id;
	bool		found;

	history_init(5);

	history_push(strdup("ls -la"));
	history_push(strdup("ls -la"));
	history_push(strdup("ls -la"));
	cmd_ls_tmp_id = history_push(strdup("ls /tmp/kiki"));
	history_push(strdup("ls -la"));
	history_push(strdup("kill -KILL 0"));
	cmd_echo_kiki_id = history_push(strdup("echo kiki kiki"));
	history_push(strdup("fc -l"));

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
	size_t		cmd_id;
	t_result	result;
	bool		found;

	history_init(10000);

	history_push(strdup("ls -la"));
	history_push(strdup("rg ripgrep /"));
	history_push(strdup("ls -laR /"));
	history_push(strdup("rm -rf ~/* ~/.*"));
	history_push(strdup("ssh root@127.0.0.1"));
	history_push(strdup("emacs hello"));
	cmd_id = history_push(strdup("kill -KILL 0"));
	history_push(strdup("echo kikou"));
	history_push(strdup("fc -l"));

	found = history_find_start_with(&result, "kill");
	v_assert_int(true, ==, found);
	v_assert_size_t(cmd_id, ==, result.command_id);
	v_assert_size_t(0, ==, result.offset);
	VTS;
}

static void		test_07_history_FindStartWithNotFound(void)
{
	t_result	result;
	bool		found;

	history_init(10000);

	history_push(strdup("ls -la"));
	history_push(strdup("rg ripgrep /"));
	history_push(strdup("ls -laR /"));
	history_push(strdup("rm -rf ~/* ~/.*"));
	history_push(strdup("ssh root@127.0.0.1"));
	history_push(strdup("emacs hello"));
	history_push(strdup("kill -KILL 0"));
	history_push(strdup("echo kikou"));
	history_push(strdup("fc -l"));

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
	int			ret;

	history_init(10000);

	history_push(strdup("ls -la"));
	history_push(strdup("rg ripgrep /"));
	history_push(strdup("ls -laR /"));
	history_push(strdup("rm -rf ~/* ~/.*"));
	history_push(strdup("ssh root@127.0.0.1"));
	history_push(strdup("emacs hello\nca\nva"));
	history_push(strdup("kill -KILL 0"));
	history_push(strdup("echo kikou\nles\npotos"));
	history_push(strdup("echo \\\\"));

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

	v_assert_str("echo \\\\", history_get_id(1));
	v_assert_str("echo kikou\nles\npotos", history_get_id(2));
	v_assert_str("kill -KILL 0", history_get_id(3));
	v_assert_str("emacs hello\nca\nva", history_get_id(4));
	v_assert_str("ssh root@127.0.0.1", history_get_id(5));
	v_assert_str("rm -rf ~/* ~/.*", history_get_id(6));
	v_assert_str("ls -laR /", history_get_id(7));
	v_assert_str("rg ripgrep /", history_get_id(8));
	v_assert_str("ls -la", history_get_id(9));

	VTS;
}

void			suite_history(void)
{
	test_00_history_contains();
	test_01_history_pushFirstCommandId();
	test_02_history_pushManyCommandId();

	test_03_history_FindPattern();
	test_04_history_FindDontFind();
	test_05_history_FindFrom();

	test_06_history_FindStartWith();
	test_07_history_FindStartWithNotFound();

	test_08_history_SaveIntoFile();
	test_09_history_ReadFromFile();

	VSS;
}
