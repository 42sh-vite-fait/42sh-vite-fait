#include "header.h"

static void		test_00_history_contains(void)
{
	t_history	history;
	size_t		command_id;
	const char	*cmd_ls = strdup("ls -la");
	const char	*cmd_echo = strdup("echo hello");
	const char	*cmd_kill = strdup("kill -KILL 0");

	history_init(&history, 3);

	history_push(&history, cmd_ls);
	history_push(&history, cmd_echo);
	history_push(&history, cmd_kill);

	v_assert_int(true, ==, history_contains(&history, 1));
	v_assert_int(true, ==, history_contains(&history, 2));
	v_assert_int(true, ==, history_contains(&history, 3));
	v_assert_int(false, ==, history_contains(&history, 4));

	v_assert_str(cmd_ls, history_get_id(&history, 1));
	v_assert_str(cmd_echo, history_get_id(&history, 2));
	v_assert_str(cmd_kill, history_get_id(&history, 3));
	v_assert_ptr(NULL, ==, history_get_id(&history, 4));
	VTS;
}

static void		test_01_history_pushFirstCommandId(void)
{
	t_history	history;
	size_t		command_id;

	history_init(&history, 10000);

	command_id = history_push(&history, strdup("ls -la"));

	v_assert_size_t(1, ==, command_id);
	VTS;
}

static void		test_02_history_pushManyCommandId(void)
{
	t_history	history;
	size_t		command_id;

	history_init(&history, 10000);

	command_id = history_push(&history, strdup("ls -la"));
	v_assert_size_t(1, ==, command_id);

	command_id = history_push(&history, strdup("ls -la"));
	v_assert_size_t(2, ==, command_id);

	command_id = history_push(&history, strdup("ls -la"));
	v_assert_size_t(3, ==, command_id);

	command_id = history_push(&history, strdup("ls -la"));
	v_assert_size_t(4, ==, command_id);

	command_id = history_push(&history, strdup("ls -la"));
	v_assert_size_t(5, ==, command_id);

	VTS;
}

static void		test_03_history_FindPattern(void)
{
	t_history	history;
	t_result	result;
	size_t		command_id;
	bool		found;

	history_init(&history, 2);

	history_push(&history, strdup("ls -la"));
	history_push(&history, strdup("ls -la"));
	history_push(&history, strdup("ls -la"));
	history_push(&history, strdup("kill -KILL 0"));
	command_id = history_push(&history, strdup("echo kiki"));
	history_push(&history, strdup("fc -l"));

	found = history_find(&result, &history, "kiki");
	v_assert_int(true, ==, found);
	v_assert_size_t(command_id, ==, result.command_id);
	v_assert_size_t(5, ==, result.offset);
	VTS;
}

static void		test_04_history_FindDontFind(void)
{
	t_history	history;
	t_result	result;
	bool		found;

	history_init(&history, 5);

	history_push(&history, strdup("ls -la"));
	history_push(&history, strdup("ls -la"));
	history_push(&history, strdup("ls -la"));
	history_push(&history, strdup("ls -la"));
	history_push(&history, strdup("ls -la"));
	history_push(&history, strdup("ls -la"));
	history_push(&history, strdup("kill -KILL 0"));
	history_push(&history, strdup("echo kikou"));
	history_push(&history, strdup("fc -l"));

	found = history_find(&result, &history, "kiki");
	v_assert_int(false, ==, found);
	VTS;
}

static void		test_05_history_FindFrom(void)
{
	t_history	history;
	t_result	result;
	size_t		cmd_ls_tmp_id;
	size_t		cmd_echo_kiki_id;
	bool		found;

	history_init(&history, 5);

	history_push(&history, strdup("ls -la"));
	history_push(&history, strdup("ls -la"));
	history_push(&history, strdup("ls -la"));
	cmd_ls_tmp_id = history_push(&history, strdup("ls /tmp/kiki"));
	history_push(&history, strdup("ls -la"));
	history_push(&history, strdup("kill -KILL 0"));
	cmd_echo_kiki_id = history_push(&history, strdup("echo kiki kiki"));
	history_push(&history, strdup("fc -l"));

	found = history_find(&result, &history, "kiki");
	v_assert_int(true, ==, found);
	v_assert_size_t(cmd_echo_kiki_id, ==, result.command_id);
	v_assert_size_t(10, ==, result.offset);

	found = history_find_from(&result, &history, "kiki", result);
	v_assert_int(true, ==, found);
	v_assert_size_t(cmd_echo_kiki_id, ==, result.command_id);
	v_assert_size_t(5, ==, result.offset);

	found = history_find_from(&result, &history, "kiki", result);
	v_assert_int(true, ==, found);
	v_assert_size_t(cmd_ls_tmp_id, ==, result.command_id);
	v_assert_size_t(8, ==, result.offset);

	found = history_find_from(&result, &history, "kiki", result);
	v_assert_int(false, ==, found);

	VTS;
}

static void		test_06_history_FindStartWith(void)
{
	t_history	history;
	size_t		cmd_id;
	t_result	result;
	bool		found;

	history_init(&history, 10000);

	history_push(&history, strdup("ls -la"));
	history_push(&history, strdup("rg ripgrep /"));
	history_push(&history, strdup("ls -laR /"));
	history_push(&history, strdup("rm -rf ~/* ~/.*"));
	history_push(&history, strdup("ssh root@127.0.0.1"));
	history_push(&history, strdup("emacs hello"));
	cmd_id = history_push(&history, strdup("kill -KILL 0"));
	history_push(&history, strdup("echo kikou"));
	history_push(&history, strdup("fc -l"));

	found = history_find_start_with(&result, &history, "kill");
	v_assert_int(true, ==, found);
	v_assert_size_t(cmd_id, ==, result.command_id);
	v_assert_size_t(0, ==, result.offset);
	VTS;
}

static void		test_07_history_FindStartWithNotFound(void)
{
	t_history	history;
	t_result	result;
	bool		found;

	history_init(&history, 10000);

	history_push(&history, strdup("ls -la"));
	history_push(&history, strdup("rg ripgrep /"));
	history_push(&history, strdup("ls -laR /"));
	history_push(&history, strdup("rm -rf ~/* ~/.*"));
	history_push(&history, strdup("ssh root@127.0.0.1"));
	history_push(&history, strdup("emacs hello"));
	history_push(&history, strdup("kill -KILL 0"));
	history_push(&history, strdup("echo kikou"));
	history_push(&history, strdup("fc -l"));

	found = history_find_start_with(&result, &history, "kikou");
	v_assert_int(false, ==, found);
	VTS;
}

#define BUFF_SIZE 4096

static char		*read_all(int fd)
{
	char		read_buff[BUFF_SIZE];
	t_buffer	buffer;
	ssize_t		ret;

	buffer_init(&buffer, BUFF_SIZE);
	while ((ret = read(fd, read_buff, BUFF_SIZE)) == BUFF_SIZE)
	{
		buffer_insert(&buffer, buffer.len, read_buff, ret);
	}
	buffer_insert(&buffer, buffer.len, read_buff, ret);
	return (buffer.str);
}

static void		test_08_history_SaveIntoFile(void)
{
	t_history	history;
	int			ret;
	int			fd;

	history_init(&history, 10000);
	fd = open("/tmp/hist.test", O_CREAT | O_RDWR | O_TRUNC, 0600);

	history_push(&history, strdup("ls -la"));
	history_push(&history, strdup("rg ripgrep /"));
	history_push(&history, strdup("ls -laR /"));
	history_push(&history, strdup("rm -rf ~/* ~/.*"));
	history_push(&history, strdup("ssh root@127.0.0.1"));
	history_push(&history, strdup("emacs hello\nca\nva"));
	history_push(&history, strdup("kill -KILL 0"));
	history_push(&history, strdup("echo kikou\nles\npotos"));
	history_push(&history, strdup("fc -l"));

	ret = history_save_into_file(&history, fd);
	v_assert_int(0, ==, ret);

	const char *file_content = "fc -l\n\
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

	lseek(fd, 0, SEEK_SET);
	v_assert_str(file_content, read_all(fd));

	VTS;
}

static void		test_09_history_ReadFromFile(void)
{
	// t_history	history;
	// int			ret;
	// int			fd;

// 	history_init(&history, 10000);
// 	fd = open("/tmp/hist.test", O_CREAT | O_RDWR | O_TRUNC, 0600);

// 	ret = history_save_into_file(&history, fd);
// 	v_assert_int(0, ==, ret);

// 	const char *file_content = "fc -l\n\
// echo kikou\\\n\
// les\\\n\
// potos\n\
// kill -KILL 0\n\
// emacs hello\\\n\
// ca\\\n\
// va\n\
// ssh root@127.0.0.1\n\
// rm -rf ~/* ~/.*\n\
// ls -laR /\n\
// rg ripgrep /\n\
// ls -la\n";

	// history_load_from_file(NULL, 0);

// 	lseek(fd, 0, SEEK_SET);
// 	v_assert_str(file_content, read_all(fd));

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

	test_08_history_SaveIntoFile(); // TODO test with multiple 'to-escape' chars
	test_09_history_ReadFromFile();

	VSS;
}
