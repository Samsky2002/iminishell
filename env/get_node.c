/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:31:27 by oakerkao          #+#    #+#             */
/*   Updated: 2023/04/24 12:46:19 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env	*get_node(char *key)
{
	t_env	*list;

	list = g_manager.list;
	while (list)
	{
		if (strcmp(key, list->key) == 0)
			return (list);
		list = list->next;	
	}
	return (0);
}
