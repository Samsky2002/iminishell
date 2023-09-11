/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:57:55 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/11 18:47:41 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fd	*new_here_list(int fd)
{
	t_fd	*head;

	head = malloc(sizeof(t_fd));
	if (!head)
		return (0);
	head->fd = fd;
	head->next = NULL;
	return (head);
}

void	add_here_list(t_fd **list, t_fd *new)
{
	t_fd	*head;

	if (!*list)
	{
		*list = new;
		return ;
	}
	head = *list;
	while (head->next)
		head = head->next;
	head->next = new;
}

void	here_list_clear(t_fd *list)
{
	t_fd	*head;

	if (!list)
		return ;
	head = list;
	while (head)
	{
		head = list->next;
		free(list);
		list = head;
	}
}

void	got_here_doc(t_exec_redirect *redirect, t_minishell *minishell)
{
	while (redirect)
	{
		if (redirect->type == T_HERE_DOC)
			minishell->here_doc = minishell->here_doc->next;
		redirect = redirect->next;
	}
}

void	here_doc_traverse(t_minishell *minishell)
{
	t_fd			*list;
	t_exec			*exec;
	t_exec_redirect	*redirect;

	exec = minishell->exec;
	list = NULL;
	while (exec)
	{
		redirect = exec->redirect;
		while (redirect)
		{
			if (redirect->type == T_HERE_DOC)
				here_doc(&list, redirect->list[0], minishell);
			redirect = redirect->next;
		}
		exec = exec->next;
	}
	minishell->here_doc = list;
}
