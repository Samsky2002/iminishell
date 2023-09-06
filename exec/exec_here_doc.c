/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:34:17 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/06 16:19:11 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//here_doc_expansion
void	got_here_doc(t_exec_redirect *redirect)
{
	while (redirect)
	{
		if (redirect->type == T_HERE_DOC)
			g_minishell.here_doc = g_minishell.here_doc->next;
		redirect = redirect->next;
	}
}

void	here_doc_traverse()
{
	t_fd	*list;
	t_fd	*tmp;
	t_exec	*exec;
	t_exec_redirect	*redirect;

	exec = g_minishell.exec;
	list = NULL;
	while (exec)
	{
		redirect = exec->redirect;
		while (redirect)
		{
			if (redirect->type == T_HERE_DOC)
				here_doc(&list, "end");
			redirect = redirect->next;
		}
		exec = exec->next;
	}
	g_minishell.here_doc = list;
}

void	here_doc(t_fd **list, char *delimiter)
{
	char	*red;
	int		p[2];

	pipe(p);
	while (1)
	{
		red = readline("here_doc>");
		if (ft_strcmp(red, delimiter) == 0)
			break ;
		ft_putstr_fd(red, p[1]);
		ft_putstr_fd("\n", p[1]);
	}
	close(p[1]);
	add_here_list(list, new_here_list(p[0]));
}
