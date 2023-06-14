/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:49:43 by oakerkao          #+#    #+#             */
/*   Updated: 2023/06/14 17:34:00 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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
