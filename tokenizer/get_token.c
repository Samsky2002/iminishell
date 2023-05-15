/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:56:31 by oakerkao          #+#    #+#             */
/*   Updated: 2023/05/13 13:17:57 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token	*get_token(t_get_type type)
{
	t_token	*list;

	list = g_manager.token;
	if (type == GET && g_manager.token)
		return (g_manager.token);
	else if (type == T_CHECK)
	{
		if (list->next)
			return (list->next);	
		else
		{
			list->type = T_NULL;
			return (0);
		}
	}
	else if (type == T_UPDATE)
	{
		if ((g_manager.token)->next)
		{
			g_manager.token = (g_manager.token)->next;
			return (g_manager.token);
		}
		else
		{
			list->type = T_NULL;
			return (0);
		}
	}
	list->type = T_NULL;
	return (0);
}
