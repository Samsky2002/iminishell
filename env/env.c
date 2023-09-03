/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:42:26 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/02 19:04:33 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_node(t_env **list, t_env *new)
{
	t_env	*head;

	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	head = *list;
	while (head->next)
		head = head->next;
	head->next = new;
}

t_env	*new_node(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	get_env_list(char **enviro)
{
	t_env	*list;
	int		i;

	list = NULL;
	i = 0;
	while (enviro[i])
	{
		add_node(&list, new_node(get_key(enviro[i]), get_value(enviro[i])));
		i++;
	}
	g_minishell.list = list;
}
