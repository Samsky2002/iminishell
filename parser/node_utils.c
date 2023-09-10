/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:49:43 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/09 13:15:56 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_list(t_arg *args, t_redirect *redirect)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	new->args = args;
	new->redirect = redirect;
	new->next = NULL;
	return (new);
}

void	add_list(t_node **list, t_node *new)
{
	t_node	*head;

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

void	node_list_clear(t_node *node)
{
	t_node	*head;

	if (!node)
		return ;
	head = node;
	while (head)
	{
		head = node->next;
		arg_list_clear(node->args);
		redirect_list_clear(node->redirect);
		free(node);
		node = head;
	}
}
