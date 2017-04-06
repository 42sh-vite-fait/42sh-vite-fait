/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node_subshell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:01:48 by djean             #+#    #+#             */
/*   Updated: 2017/04/08 15:14:53 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <signal.h>
#include <stdlib.h>
#include "exec.h"
#include "ast.h"
#include "sig.h"
#include "exit_status.h"
#include "errors.h"
#include "opt.h"

extern t_tree_walker	*const g_walkers[];

int		exec_node_subshell(const t_ast_node *node, const t_string *input,
		bool set_context)
{
	pid_t	subshell;
	int		status;

	assert(node != NULL);
	if (exec_fork(&subshell) != OK_)
		return (-1);
	if (subshell == 0)
	{
		if (set_context)
			exec_child_set_context();
		if (exec_redirection(node->command.redirections, input) != OK_)
		{
			error_print("execution");
			_exit(-1);
		}
		_exit(g_walkers[node->left->type](node->left, input, false));
	}
	else
		status = exec_parent_wait_child_process_group(subshell, set_context);
	return (status);
}
