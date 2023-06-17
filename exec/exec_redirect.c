/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:45:09 by oakerkao          #+#    #+#             */
/*   Updated: 2023/06/17 13:29:27 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	out(char **path)
{
	int	fd;

	fd = open(*path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		printf("error\n");
	//dup2(fd, 1);
}

void	in(char **path)
{
	int	fd;

	fd = open(*path, O_RDONLY);
	if (fd == -1)
		printf("error\n");
	//dup2(fd, 0);

}

void	append(char **path)
{
	int	fd;

	fd = open(*path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		printf("error\n");
	//dup2(fd, 1);
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
		redirect = redirect->next;
	}
}
