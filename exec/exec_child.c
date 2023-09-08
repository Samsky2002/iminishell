/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:30:53 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/08 11:52:33 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parent_builtins_check(char **arr)
{
	if (!arr || !*arr)
		return (0);
	else if (strcmp(arr[0], "cd") == 0)
		return (1);
	else if (strcmp(arr[0], "export") == 0)
		return (1);
	else if (strcmp(arr[0], "unset") == 0)
		return (1);
	else if (strcmp(arr[0], "exit") == 0)
		return (1);
	return (0);
	exit(g_minishell.exit_s);
}

int	child_builtins_check(char **arr)
{
	if (!arr || !*arr)
		return (0);
	if (strcmp(arr[0], "echo") == 0)
		return (1);
	else if (strcmp(arr[0], "pwd") == 0)
		return (1);
	else if (strcmp(arr[0], "env") == 0)
		return (1);
	else if (strcmp(arr[0], "cd") == 0)
		return (1);
	else if (strcmp(arr[0], "export") == 0)
		return (1);
	else if (strcmp(arr[0], "unset") == 0)
		return (1);
	else if (strcmp(arr[0], "exit") == 0)
		return (1);
	return (0);
}

void	child_builtins(char **arr)
{
	if (!arr || !*arr)
		return ;
	if (strcmp(arr[0], "echo") == 0)
		echo(arr);
	else if (strcmp(arr[0], "pwd") == 0)
		pwd();
	else if (strcmp(arr[0], "env") == 0)
		env();
}

void	parent_builtins(char **arr)
{
	if (!arr || !*arr)
		return ;
	else if (strcmp(arr[0], "cd") == 0)
		cd(arr[1]);
	else if (strcmp(arr[0], "export") == 0)
		export(arr);
	else if (strcmp(arr[0], "unset") == 0)
		unset(arr);
	else if (strcmp(arr[0], "exit") == 0)
		ft_exit(arr);
}

void	close_child_pipes(int **pipes, int i, int len, t_exec_redirect *redirect_list)
{
	int	j;

	j = 0;
	if (i != 0)
		dup2(pipes[i - 1][0], 0);
	if (i != len - 1)
		dup2(pipes[i][1], 1);
	while (j < len - 1)
	{
		if (j != 0)
			close(pipes[j][0]);
		if (j != len - 1)
			close(pipes[j][1]);
		j++;
	}
	redirect(redirect_list);
}

void	exec_child(t_exec *exec)
{
	t_exec_redirect	*redirect_list;
	char			**args;
	char			*cmd;

	redirect_list = exec->redirect;
	args = exec->args;
	redirect(redirect_list);
	if (child_builtins_check(args))
	{
		child_builtins(args);
		exit(g_minishell.exit_s);
	}
	cmd = path_getter(args[0]);
	if (g_minishell.mini_error == SUCCESS)
	{
		if (execve(cmd , args, NULL) == -1)
		{
			exec_error();
			exec_error_msg();
			exit(g_minishell.exit_s);
		}
	}
	exec_error();
	exec_error_msg();
	exit(g_minishell.exit_s);
}

// exec_args pointer gets lost
// when i don't protect the if condition if there is an error with the file he enters the execve
