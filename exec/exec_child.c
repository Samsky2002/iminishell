/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:30:53 by oakerkao          #+#    #+#             */
/*   Updated: 2023/06/17 13:48:32 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	builtins(char **arr)
{
	if (!arr)
		return ;
	if (strcmp(arr[0], "echo") == 0)	
		echo(arr);
	else if (strcmp(arr[0], "cd") == 0)	
		cd(arr[0]);
	else if (strcmp(arr[0], "pwd") == 0)	
		pwd();
	else if (strcmp(arr[0], "env") == 0)	
		env();
	else if (strcmp(arr[0], "export") == 0)	
		export(arr);
	else if (strcmp(arr[0], "unset") == 0)	
		unset(arr);
	else if (strcmp(arr[0], "exit") == 0)	
		ft_exit(arr);
}

void	exec_child(t_context *ctx)
{
	t_exec	*exec;

	exec = g_minishell.exec;
	redirect(exec->redirect);
	if (fork() == 0)
	{
		dup2(ctx->fd[0], 0);
		dup2(ctx->fd[1], 1);
		builtins(exec->args);
		//execve("/bin/ls", exec->args, NULL);
		//execve(get_path(exec->args[0]), exec->args, NULL);
		exit(1);
	}
}
