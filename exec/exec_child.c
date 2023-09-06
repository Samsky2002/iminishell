/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:30:53 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/06 15:44:44 by oakerkao         ###   ########.fr       */
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
	exit(0);
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

void	exec_child(t_exec *exec, int i, int len, int **pipes)
{
	int				j;
	t_exec_redirect	*redirect_list;
	char			**args;

	redirect_list = exec->redirect;
	args = exec->args;
	j = 0;
	if (i != 0)
		dup2(pipes[i - 1][0], 0);
	if (i != len - 1)
		dup2(pipes[i][1], 1);
	redirect(redirect_list);
	while (j < len - 1)
	{
		if (j != 0)
			close(pipes[j][0]);
		if (j != len - 1)
			close(pipes[j][1]);
		j++;
	}
	if (child_builtins_check(args))
	{
		child_builtins(args);
		exit(0);
	}
	if (args[0])
	{
		execve(path_getter(args[0]), args, NULL);
		printf("test\n");
	}
	exit(0);
}

// exec_args pointer gets lost
