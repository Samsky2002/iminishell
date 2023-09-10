/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:21:12 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/08 19:01:46 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*new_arg(char *arg)
{
	t_arg	*new;

	new = malloc(sizeof(t_arg));
	new->arg = ft_strdup(arg);
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

void	arg_list_clear(t_arg *arg)
{
	t_arg	*head;

	if (!arg)
		return ;
	head = arg;
	while (head)
	{
		head = arg->next;
		free(arg->arg);
		free(arg);
		arg = head;
	}
}
