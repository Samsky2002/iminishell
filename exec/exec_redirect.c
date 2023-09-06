/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:45:09 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/06 15:41:50 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	out(char **path)
{
	int	fd;

	fd = open(*path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		printf("error\n");
	dup2(fd, 1);
	close(fd);
}

void	in(char **path)
{
	int	fd;

	fd = open(*path, O_RDONLY);
	if (fd == -1)
		printf("error\n");
	dup2(fd, 0);
	close(fd);
}

void	append(char **path)
{
	int	fd;

	fd = open(*path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		printf("error\n");
	dup2(fd, 1);
	close(fd);
}

void	here_doc_app()
{
	dup2((g_minishell.here_doc)->fd, 0);
	close((g_minishell.here_doc)->fd);
	g_minishell.here_doc = g_minishell.here_doc->next;
}

void	redirect(t_exec_redirect *redirect)
{
	while (redirect)
	{
		if (redirect->type == T_OUT)
			out(redirect->list);
		else if (redirect->type == T_IN)
			in(redirect->list);
		else if (redirect->type == T_APPEND)
			append(redirect->list);
		else if (redirect->type == T_HERE_DOC)
			here_doc_app();
		redirect = redirect->next;
	}
}
