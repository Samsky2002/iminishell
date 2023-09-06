/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:57:55 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/06 13:12:56 by oakerkao         ###   ########.fr       */
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
