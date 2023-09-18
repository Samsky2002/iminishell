/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:08:00 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/14 18:40:24 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec_redirect	*new_exec_redirect(char **arr, t_token_type type)
{
	t_exec_redirect	*new;

	new = malloc(sizeof(t_exec_redirect));
	new->type = type;
	new->list = arr;
	new->next = NULL;
	return (new);
}

void	add_exec_redirect(t_exec_redirect **redirect, t_exec_redirect *new)
{
	t_exec_redirect	*head;

	while (!*redirect)
	{
		*redirect = new;
		return ;
	}
	head = *redirect;
	while (head->next)
		head = head->next;
	head->next = new;
}

void	exec_child_clear(t_minishell *minishell)
{
	node_list_clear(minishell->node);
	exec_list_clear(minishell->exec);
	env_list_clear(minishell->env);
}
