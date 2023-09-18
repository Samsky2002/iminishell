/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:30:53 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/15 11:53:59 by oakerkao         ###   ########.fr       */
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

void	child_builtins(char **arr, t_minishell *minishell)
{
	if (!arr || !*arr)
		return ;
	if (strcmp(arr[0], "echo") == 0)
		echo(arr);
	else if (strcmp(arr[0], "pwd") == 0)
		pwd();
	else if (strcmp(arr[0], "env") == 0)
		env(minishell);
	else if (strcmp(arr[0], "export") == 0 && !arr[1])
		export(arr, minishell);
	if (strcmp(arr[0], "export"))
		exec_error(minishell);
}

void	parent_builtins(char **arr, t_minishell *minishell)
{
	if (!arr || !*arr)
		return ;
	if (strcmp(arr[0], "cd") == 0)
		cd(arr[1], minishell);
	else if (strcmp(arr[0], "export") == 0 && arr[1])
		export(arr, minishell);
	else if (strcmp(arr[0], "unset") == 0)
		unset(arr, minishell);
	else if (strcmp(arr[0], "exit") == 0)
		ft_exit(arr, minishell);
	if (strcmp(arr[0], "export"))
	{
		exec_error(minishell);
		exec_error_msg(minishell);
	}
}

void	exec_child(t_minishell *minishell, t_exec *exec)
{
	t_exec_redirect	*redirect_list;
	char			**args;
	char			*path;

	redirect_list = exec->redirect;
	args = exec->args;
	redirect(redirect_list, minishell);
	if (minishell->mini_error == SUCCESS)
	{
		if (child_builtins_check(args))
			child_builtins(args, minishell);
		else
		{
			path = path_getter(args[0], minishell);
			if (path)
				exec_child_helper(args, minishell, path);
			exec_error(minishell);
			exec_error_msg(minishell);
		}
	}
	exec_child_clear(minishell);
	exit(minishell->exit_s);
}
