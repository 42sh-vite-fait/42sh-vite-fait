#include "header.h"
#include "criterion/criterion.h"

t_editenv env;

static void setup(void) {
	ft_memset(&env, 0, sizeof(t_editenv));
	string_init(&env.rbuff);
	string_init(&env.cpy);
	string_init(&env.entry);
	string_init(&env.initial_entry);
	env.entry_index = 0;
	env.selection_size = 1;
	env.cpos.x = (int)(prompt() + 1);
}

static void teardown(void) {
	string_shutdown(&env.rbuff);
	string_shutdown(&env.cpy);
	string_shutdown(&env.entry);
	string_shutdown(&env.initial_entry);
}

TestSuite(env, .init = setup, .fini = teardown);

Test(env, Prompt) {
	cr_assert_eq(prompt(), 6);
}

Test(env, Execute_handler) {
	env.entry_index = 1;
	env.rbuff.str[0] = 27;
	env.rbuff.str[1] = '[';
	env.rbuff.str[2] = 'A';
	env.rbuff.str[3] = 0;
	ui_execute_handler(&env);
	env.rbuff_index++;
	ui_execute_handler(&env);
	env.rbuff_index++;
	ui_execute_handler(&env);
	env.rbuff_index++;
	cr_assert_eq(0, env.entry_index);
}

Test(env, ui_leave) {
	env.entry.len = 1;
	ui_leave(&env);
	cr_assert_eq(env.must_leave, 0);
	env.entry.len = 0;
	ui_leave(&env);
	cr_assert_eq(env.must_leave, 1);
}

Test(env, ui_change_case) {
	env.entry.len = 3;
	env.entry.str[0] = 'A';
	env.entry.str[1] = 'b';
	env.entry.str[2] = 'A';
	env.entry.str[3] = 0;
	ui_change_case(&env);
	cr_assert_eq(strcmp("aBa", env.entry.str), 0);
}

Test(env, ui_handler_insert_char) {
	env.rbuff.str[0] = 'B';
	ui_handler_insert_char(&env);
	cr_assert_eq(1, env.entry.len);
}

Test(env, ui_handler_copy_paste) {
	env.entry.str[0] = 'K';
	env.entry.str[1] = 'E';
	env.entry.str[2] = 'K';
	env.entry.len = 3;
	env.is_selecting = 1;
	env.selection_size = 3;
	ui_handler_copy(&env);
	cr_assert_eq(strcmp(env.cpy.str, "KEK"), 0);
	ui_handler_paste(&env);
	cr_assert_eq(strcmp(env.entry.str, "KEKKEK"), 0);
}

Test(env, ui_handler_cut_paste) {
	env.entry.str[0] = 'K';
	env.entry.str[1] = 'E';
	env.entry.str[2] = 'K';
	env.entry.len = 3;
	env.is_selecting = 1;
	env.selection_size = 3;
	ui_handler_cut(&env);
	cr_assert_eq(strcmp(env.cpy.str, "KEK"), 0);
	cr_assert_eq(strcmp(env.entry.str, ""), 0);
	ui_handler_paste(&env);
	cr_assert_eq(strcmp(env.entry.str, "KEK"), 0);
}


Test(env, ui_handler_move_right_word) {
	ft_memcpy(env.entry.str, "Je mapelle Constantin et je suis un lapin.", strlen("Je mapelle Constantin et je suis un lapin."));
	env.entry_index = 14;
	env.entry.len = strlen("Je mapelle Constantin et je suis un lapin.");
	ui_handler_move_right_word(&env);
	cr_assert_eq(env.entry_index, 22);
}

Test(env, ui_handler_move_left_word) {
	ft_memcpy(env.entry.str, "Je mapelle Constantine et je bouffe des pines.", strlen("Je mapelle Constantine et je bouffe des pines."));
	env.entry_index = 14;
	env.entry.len = strlen("Je mapelle Constantine et je bouffe des pines.");
	ui_handler_move_left_word(&env);
	cr_assert_eq(env.entry_index, 9);
}

Test(env, ui_handler_move_right_word_no_next_word) {
	ft_memcpy(env.entry.str, "Je mapelle Constantine et je bouffe des pines.", strlen("Je mapelle Constantine et je bouffe des pines."));
	env.entry_index = 44;
	env.entry.len = strlen("Je mapelle Constantine et je bouffe des pines.");
	ui_handler_move_right_word(&env);
	cr_assert_eq(env.entry_index, 44);
}
