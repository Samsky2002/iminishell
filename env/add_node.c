/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:46:02 by oakerkao          #+#    #+#             */
/*   Updated: 2023/06/14 15:01:25 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	add_node(t_env *new)
{
	t_env	*list;

	if (g_minishell.list == NULL)
	{
		g_minishell.list = new;
		return ;	
	}
	list = g_minishell.list;
	while (list->next)
		list = list->next;
	list->next = new;
}

void	free_env_list()
{
	t_env	*list;

	list = g_minishell.list;
	if (!g_minishell.list)
		return ;
	while (list)
	{
		list = g_minishell.list->next;
		free(g_minishell.list->key);
		free(g_minishell.list->value);
		free(g_minishell.list);
		g_minishell.list = list;
	}
}
