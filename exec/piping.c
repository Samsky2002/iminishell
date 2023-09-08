/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:32:59 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/08 11:16:28 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child_prep(t_exec *exec, int prev_pipe_read, int pipes[2])
{
	if (prev_pipe_read != -1)
	{
		dup2(prev_pipe_read, 0);
		close(prev_pipe_read);
	}
	if (exec->next != NULL)
		dup2(pipes[1], 1);
	close(pipes[0]);
	close(pipes[1]);
	exec_child(exec);

}

void	piping_loop(t_exec *exec)
{
	int	pipes[2];
	int	pid;
	int	prev_pipe_read;

	while (exec)
	{
		if (parent_builtins_check(exec->args) && exec->next == NULL)
			parent_builtins(exec->args);
		pipe(pipes);
		if (fork() == 0)
		{
			exec_child_prep(exec, prev_pipe_read, pipes);
		}
		if (prev_pipe_read != -1)
			close(prev_pipe_read);
		close(pipes[1]);
		prev_pipe_read = pipes[0];
		got_here_doc(exec->redirect);
		exec = exec->next;
	}
	if (prev_pipe_read != -1)
		close(prev_pipe_read);
}

void	free_twod_int_array(int **arr, int len)
{
	int	i;

	i = 0;
	while (i < len - 1)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	piping()
{
	t_exec	*exec;
	int	status;
	t_fd	*fd;

	fd = g_minishell.here_doc;
	exec = g_minishell.exec;
	piping_loop(exec);
	while (wait(&status) > 0) {};
	if (WIFEXITED(status))
		g_minishell.exit_s = WEXITSTATUS(status);
	g_minishell.here_doc = fd;
	here_list_clear(g_minishell.here_doc);
}

/*here_doc_gets_incrementes in the child process
/ be careful what happens in child doens't affect parent*/
/*
 * free pid
 * free pipes
 * free exec list
 * free here_doc linked list
 */
