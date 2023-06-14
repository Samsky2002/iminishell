/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:21:12 by oakerkao          #+#    #+#             */
/*   Updated: 2023/06/14 16:43:15 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_arg	*new_arg(char *arg)
{
	t_arg	*new;

	new = malloc(sizeof(t_arg));
	new->arg = arg;
	new->next = NULL;
	return (new);
}

void	add_arg(t_arg **list, t_arg *new)
{
	t_arg	*head;

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
