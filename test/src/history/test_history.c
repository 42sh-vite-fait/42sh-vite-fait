#include "header.h"
#include "criterion/criterion.h"
#include "criterion/redirect.h"

#define BUFF_SIZE	(4096)

extern t_history	g_history;

TestSuite(history);

Test(history, contains) {

	size_t		command_id;
	t_string	cmd_ls;
	t_string	cmd_echo;
	t_string	cmd_kill;

	history_init(3);

	string_dup(&cmd_ls, "ls -la");
	string_dup(&cmd_echo, "echo hello");
	string_dup(&cmd_kill, "kill -KILL 0");

	history_add(&cmd_ls);
	history_add(&cmd_echo);
	history_add(&cmd_kill);

	cr_assert_not_null(history_get(1));
	cr_assert_not_null(history_get(2));
	cr_assert_not_null(history_get(3));
	cr_assert_null(history_get(4));

	cr_assert_str_eq(cmd_ls.str, history_get(1)->str);
	cr_assert_str_eq(cmd_echo.str, history_get(2)->str);
	cr_assert_str_eq(cmd_kill.str, history_get(3)->str);
	cr_assert_null(history_get(4));

	history_shutdown();
}

Test(history, clear) {

	size_t		command_id;
	t_string	cmd_ls;
	t_string	cmd_echo;
	t_string	cmd_kill;

	history_init(3);

	string_dup(&cmd_ls, "ls -la");
	string_dup(&cmd_echo, "echo hello");
	string_dup(&cmd_kill, "kill -KILL 0");

	history_add(&cmd_ls);
	history_add(&cmd_echo);
	history_add(&cmd_kill);

	cr_assert_not_null(history_get(1));
	cr_assert_not_null(history_get(2));
	cr_assert_not_null(history_get(3));
	cr_assert_null(history_get(4));

	cr_assert_str_eq(cmd_ls.str, history_get(1)->str);
	cr_assert_str_eq(cmd_echo.str, history_get(2)->str);
	cr_assert_str_eq(cmd_kill.str, history_get(3)->str);
	cr_assert_null(history_get(4));

	history_clear();

	cr_assert_null(history_get(1));
	cr_assert_null(history_get(2));
	cr_assert_null(history_get(3));
	cr_assert_null(history_get(4));

	cr_assert_eq(0, history_get_last_id());

	history_shutdown();
}

Test(history, add_first_command_id) {

	t_string	command;
	size_t		command_id;

	history_init(10000);

	string_dup(&command, "ls -la");
	command_id = history_add(&command);

	cr_assert_eq(1, command_id);

	history_shutdown();
}

Test(history, add_commad_with_trailing_nl) {

	t_string	command;

	history_init(20);

	string_dup(&command, "ls -la\n");
	cr_assert_eq(1, history_add(&command));

	cr_assert_str_eq("ls -la", history_get(1)->str);

	history_shutdown();
}

Test(history, add_many_command_id) {

	t_string	command;
	size_t		command_id;

	history_init(10000);

	string_dup(&command, "ls -la");
	command_id = history_add(&command);
	cr_assert_eq(1, command_id);

	string_dup(&command, "ls -la");
	command_id = history_add(&command);
	cr_assert_eq(2, command_id);

	string_dup(&command, "ls -la");
	command_id = history_add(&command);
	cr_assert_eq(3, command_id);

	string_dup(&command, "ls -la");
	command_id = history_add(&command);
	cr_assert_eq(4, command_id);

	string_dup(&command, "ls -la");
	command_id = history_add(&command);
	cr_assert_eq(5, command_id);

	history_shutdown();
}

Test(history, find_pattern) {

	t_string	command;
	t_result	result;
	size_t		command_id;
	bool		found;

	history_init(2);

	string_dup(&command, "ls -la");
	history_add(&command);

	string_dup(&command, "ls -la");
	history_add(&command);

	string_dup(&command, "ls -la");
	history_add(&command);

	string_dup(&command, "kill -KILL 0");
	history_add(&command);

	string_dup(&command, "echo kiki");
	command_id = history_add(&command);

	string_dup(&command, "fc -l");
	history_add(&command);

	found = history_find(&result, "kiki");
	cr_assert_eq(true, found);
	cr_assert_eq(command_id, result.command_id);
	cr_assert_eq(5, result.offset);

	history_shutdown();
}

Test(history, find_dont_find) {

	t_string	command;
	t_result	result;
	bool		found;

	history_init(5);
	string_dup(&command, "ls -la");
	history_add(&command);

	string_dup(&command, "ls -la");
	history_add(&command);

	string_dup(&command, "ls -la");
	history_add(&command);

	string_dup(&command, "ls -la");
	history_add(&command);

	string_dup(&command, "ls -la");
	history_add(&command);

	string_dup(&command, "ls -la");
	history_add(&command);

	string_dup(&command, "kill -KILL 0");
	history_add(&command);

	string_dup(&command, "echo kikou");
	history_add(&command);

	string_dup(&command, "fc -l");
	history_add(&command);

	found = history_find(&result, "kiki");
	cr_assert_eq(false, found);

	history_shutdown();
}

Test(history, find_from) {

	t_result	result;
	t_string	command;
	size_t		cmd_ls_tmp_id;
	size_t		cmd_echo_kiki_id;
	size_t		cmd_echo_llll_id;
	bool		found;

	history_init(6);

	string_dup(&command, "ls -la");
	history_add(&command);

	string_dup(&command, "ls -la");
	history_add(&command);

	string_dup(&command, "ls -la");
	history_add(&command);

	string_dup(&command, "ls /tmp/kiki");
	cmd_ls_tmp_id = history_add(&command);

	string_dup(&command, "ls -la");
	history_add(&command);

	string_dup(&command, "kill -KILL 0");
	history_add(&command);

	string_dup(&command, "echo kiki kiki");
	cmd_echo_kiki_id = history_add(&command);

	string_dup(&command, "fc -l");
	history_add(&command);

	string_dup(&command, "echo lllllll");
	cmd_echo_llll_id = history_add(&command);

	found = history_find(&result, "kiki");
	cr_assert_eq(true, found);
	cr_assert_eq(cmd_echo_kiki_id, result.command_id);
	cr_assert_eq(10, result.offset);

	found = history_find_from(&result, "kiki", result);
	cr_assert_eq(true, found);
	cr_assert_eq(cmd_echo_kiki_id, result.command_id);
	cr_assert_eq(5, result.offset);

	found = history_find_from(&result, "kiki", result);
	cr_assert_eq(true, found);
	cr_assert_eq(cmd_ls_tmp_id, result.command_id);
	cr_assert_eq(8, result.offset);

	found = history_find_from(&result, "kiki", result);
	cr_assert_eq(false, found);

	found = history_find(&result, "l");
	cr_assert_eq(true, found);
	cr_assert_eq(cmd_echo_llll_id, result.command_id);
	cr_assert_eq(11, result.offset);

	found = history_find_from(&result, "l", result);
	cr_assert_eq(true, found);
	cr_assert_eq(cmd_echo_llll_id, result.command_id);
	cr_assert_eq(10, result.offset);

	found = history_find_from(&result, "l", result);
	cr_assert_eq(true, found);
	cr_assert_eq(cmd_echo_llll_id, result.command_id);
	cr_assert_eq(9, result.offset);

	found = history_find_from(&result, "l", result);
	cr_assert_eq(true, found);
	cr_assert_eq(cmd_echo_llll_id, result.command_id);
	cr_assert_eq(8, result.offset);

	history_shutdown();
}

Test(history, find_start_with) {

	t_result	result;
	t_string	command;
	size_t		cmd_id;
	bool		found;

	history_init(10000);

	string_dup(&command, "ls -la");
	history_add(&command);

	string_dup(&command, "rg ripgrep /");
	history_add(&command);

	string_dup(&command, "ls -laR /");
	history_add(&command);

	string_dup(&command, "rm -rf ~/* ~/.*");
	history_add(&command);

	string_dup(&command, "ssh root@127.0.0.1");
	history_add(&command);

	string_dup(&command, "emacs hello");
	history_add(&command);

	string_dup(&command, "kill -KILL 0");
	cmd_id = history_add(&command);

	string_dup(&command, "echo kikou");
	history_add(&command);

	string_dup(&command, "fc -l");
	history_add(&command);

	found = history_find_start_with(&result, "kill");
	cr_assert_eq(true, found);
	cr_assert_eq(cmd_id, result.command_id);
	cr_assert_eq(0, result.offset);

	history_shutdown();
}

Test(history, find_start_with_not_found) {

	t_string	command;
	t_result	result;
	bool		found;

	history_init(10000);

	string_dup(&command, "ls -la");
	history_add(&command);

	string_dup(&command, "rg ripgrep /");
	history_add(&command);

	string_dup(&command, "ls -laR /");
	history_add(&command);

	string_dup(&command, "rm -rf ~/* ~/.*");
	history_add(&command);

	string_dup(&command, "ssh root@127.0.0.1");
	history_add(&command);

	string_dup(&command, "emacs hello");
	history_add(&command);

	string_dup(&command, "kill -KILL 0");
	history_add(&command);

	string_dup(&command, "echo kikou");
	history_add(&command);

	string_dup(&command, "fc -l");
	history_add(&command);

	found = history_find_start_with(&result, "kikou");
	cr_assert_eq(false, found);

	history_shutdown();
}

Test(history, save_into_file) {

	const char	*hist_file = "/tmp/save_into_file.txt";
	t_string	command;
	int			ret;

	remove(hist_file);

	history_init(10000);

	string_dup(&command, "ls -la");
	history_add(&command);

	string_dup(&command, "rg ripgrep /");
	history_add(&command);

	string_dup(&command, "ls -laR /");
	history_add(&command);

	string_dup(&command, "rm -rf ~/* ~/.*");
	history_add(&command);

	string_dup(&command, "ssh root@127.0.0.1");
	history_add(&command);

	string_dup(&command, "emacs hello\nca\nva");
	history_add(&command);

	string_dup(&command, "kill -KILL 0");
	history_add(&command);

	string_dup(&command, "echo kikou\nles\npotos");
	history_add(&command);

	string_dup(&command, "echo \\\\");
	history_add(&command);

	ret = history_save_into_file(hist_file);
	cr_assert_eq(0, ret);

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

	cr_assert_file_contents_eq_str(fopen(hist_file, "r"), file_content);

	history_shutdown();
}

Test(history, load_from_file_exist) {

	const char	*hist_file = "/tmp/load_from_file_exist.txt";
	int			ret;

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

	int fd = open(hist_file, O_CREAT | O_TRUNC | O_WRONLY, 0600);
	cr_assert_neq(-1, fd);
	dprintf(fd, "%s", file_content);
	close(fd);

	history_init(10000);

	ret = history_load_from_file(hist_file);
	cr_assert_eq(0, ret);

	cr_assert_str_eq("echo \\\\", history_get(1)->str);
	cr_assert_str_eq("echo kikou\nles\npotos", history_get(2)->str);
	cr_assert_str_eq("kill -KILL 0", history_get(3)->str);
	cr_assert_str_eq("emacs hello\nca\nva", history_get(4)->str);
	cr_assert_str_eq("ssh root@127.0.0.1", history_get(5)->str);
	cr_assert_str_eq("rm -rf ~/* ~/.*", history_get(6)->str);
	cr_assert_str_eq("ls -laR /", history_get(7)->str);
	cr_assert_str_eq("rg ripgrep /", history_get(8)->str);
	cr_assert_str_eq("ls -la", history_get(9)->str);
	cr_assert_null(history_get(10));

	history_shutdown();
}

Test(history, load_from_file_doesnt_exists) {

	const char	*hist_file = "/tmp/load_from_file_doesnt_exists.txt";
	int			ret;

	remove(hist_file);

	history_init(10000);

	ret = history_load_from_file(hist_file);
	cr_assert_eq(-1, ret);

	history_shutdown();
}

Test(history, load_from_file_not_readable) {

	const char	*hist_file = "/tmp/load_from_file_not_readable.txt";
	int			ret;

	int fd;
	remove(hist_file);
	fd = open(hist_file, O_CREAT, 0000);
	cr_assert_neq(-1, fd);
	close(fd);

	history_init(10000);

	ret = history_load_from_file(hist_file);
	cr_assert_eq(-1, ret);

	history_shutdown();
}
