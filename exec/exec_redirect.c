/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:45:09 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/09 20:40:42 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	twod_array_size(char **arr)
{
	int		i;

	i = 0;
	while (arr && arr[i])
	{
		i++;
	}
	return (i);
}

void	out(char **path, t_minishell *minishell)
{
	int	fd;
	int	i;

	i = 0;
	if (!path || !*path || twod_array_size(path) > 1)
	{
		minishell->mini_error = AMBIGUOUS;
		return ;
	}
	fd = open(*path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		if (!access(*path, F_OK))
		{
			if (access(*path, W_OK))
				minishell->mini_error = PERMISSION_DENIED_FILE;
		}
		else
			minishell->mini_error = NO_SUCH_FILE;
		return ;
	}
	dup2(fd, 1);
	close(fd);
}

void	in(char **path, t_minishell *minishell)
{
	int	fd;

	fd = open(*path, O_RDONLY);
	if (!path || !*path || twod_array_size(path) > 1)
	{
		minishell->mini_error = AMBIGUOUS;
		return ;
	}
	if (fd == -1)
	{
		if (!access(*path, F_OK))
		{
			if (access(*path, R_OK))
				minishell->mini_error = PERMISSION_DENIED_FILE;
		}
		else
			minishell->mini_error = NO_SUCH_FILE;
		return ;
	}
	dup2(fd, 0);
	close(fd);
}

void	append(char **path, t_minishell *minishell)
{
	int	fd;

	if (!path || !*path || twod_array_size(path) > 1)
	{
		minishell->mini_error = AMBIGUOUS;
		return ;
	}
	fd = open(*path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		if (!access(*path, F_OK))
		{
			if (access(*path, W_OK))
				minishell->mini_error = PERMISSION_DENIED_FILE;
		}
		else
			minishell->mini_error = NO_SUCH_FILE;
		return ;
	}
	dup2(fd, 1);
	close(fd);
}

void	here_doc_app(t_minishell *minishell)
{
	dup2((minishell->here_doc)->fd, 0);
	close((minishell->here_doc)->fd);
	minishell->here_doc = minishell->here_doc->next;
}

void	redirect(t_exec_redirect *redirect, t_minishell *minishell)
{
	if (!redirect)
		return ;
	while (redirect)
	{
		if (redirect->type == T_OUT)
			out(redirect->list, minishell);
		else if (redirect->type == T_IN)
			in(redirect->list, minishell);
		else if (redirect->type == T_APPEND)
			append(redirect->list, minishell);
		else if (redirect->type == T_HERE_DOC)
			here_doc_app(minishell);
		redirect = redirect->next;
	}
	exec_error(minishell);
	exec_error_msg(minishell);
}
