/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:32:59 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/15 12:31:41 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child_helper(char	**args, t_minishell *minishell, char *path)
{
	execve(path, args, minishell->enviro);
	if (minishell->mini_error == SUCCESS)
	{
		perror("minishell");
		exec_child_clear(minishell);
		exit(1);
	}
}

void	exec_child_prep(t_exec *exec, t_minishell *minishell, \
		int prev_pipe_read, int pipes[2])
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
	exec_child(minishell, exec);
}

int	exec_list_len(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec)
	{
		i++;
		exec = exec->next;
	}
	return (i);
}

void	piping_loop(t_minishell *minishell)
{
	int		pipes[2];
	int		prev_pipe_read;
	t_exec	*exec;

	exec = minishell->exec;
	prev_pipe_read = -1;
	while (exec)
	{
		if (parent_builtins_check(exec->args) && \
				exec_list_count(minishell->exec) == 1)
			parent_builtins(exec->args, minishell);
		pipe(pipes);
		if (fork() == 0)
			exec_child_prep(exec, minishell, prev_pipe_read, pipes);
		if (prev_pipe_read != -1)
			close(prev_pipe_read);
		close(pipes[1]);
		prev_pipe_read = pipes[0];
		got_here_doc(exec->redirect, minishell);
		exec = exec->next;
	}
	if (prev_pipe_read != -1)
		close(prev_pipe_read);
}

void	piping(t_minishell *minishell)
{
	t_exec	*exec;
	int		status;
	t_fd	*fd;

	fd = minishell->here_doc;
	exec = minishell->exec;
	piping_loop(minishell);
	while (wait(&status) > 0)
	{
		if (g_sig[1] == 0)
		{
			if (WIFEXITED(status))
				minishell->exit_s = WEXITSTATUS(status);
		}
		else
			minishell->exit_s = g_sig[1];
	}
	minishell->here_doc = fd;
	here_list_clear(minishell->here_doc);
}
