/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:32:59 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/06 16:18:17 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**opening_pipes(int process_num)
{
	int	i;
	int	**pipes;

	i = 0;
	pipes = malloc((process_num - 1) * sizeof(int *));
	while (i < process_num - 1)
	{
		pipes[i] = malloc(2 * sizeof(int));
		i++;
	}
	i = 0;
	while (i < process_num - 1)
	{
		pipe(pipes[i]);
		i++;
	}
	return (pipes);
}

void	close_parent(int **pipes, int len)
{
	int	i;

	i = 0;
	while (i < len - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < len)
	{
		wait(NULL);
		i++;
	}
}

void	piping()
{
	int		*pid;
	int		**pipes;
	int		len;
	int		i;
	t_exec	*exec;
	t_fd	*fd;

	fd = g_minishell.here_doc;
	exec = g_minishell.exec;
	len = exec_list_count(exec);
	pid = malloc(len * sizeof(int));
	pipes = opening_pipes(len);
	i = 0;
	//here_doc_gets_incrementes in the child process
	while (i < len)
	{
		if (parent_builtins_check(exec->args) && len == 1)
			parent_builtins(exec->args);
		pid[i] = fork();
		if (pid[i] == 0)
			exec_child(exec, i, len, pipes);
		got_here_doc(exec->redirect);
		exec = exec->next;
		i++;
	}
	g_minishell.here_doc = fd;
	close_parent(pipes, len);
}

// be careful what happens in child doens't affect parent
