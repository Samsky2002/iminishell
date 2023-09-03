/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:32:25 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/03 11:32:42 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *str)
{
	int		len;
	char	*new;

	if (!str)
		return (0);
	if (ft_strchr(str, '=') == NULL)
		len = ft_strlen(str) + 1;
	else
	{
		new = ft_strchr(str, '=');
		len = new - str + 1;
	}
	new = malloc(len * sizeof(char));
	ft_strlcpy(new, str, len);
	return (new);
}

char	*get_value(char *str)
{
	int		len;
	char	*new;

	if (ft_strchr(str, '=') == NULL)
		return (0);
	else
	{
		str = ft_strchr(str, '=');
		str++;
		len = ft_strlen(str) + 1;
	}
	new = malloc(len);
	ft_strlcpy(new, str, len);
	return (new);
}

t_env	*get_node(char *key)
{
	t_env	*list;

	if (!key)
		return (0);
	list = g_minishell.list;
	while (list)
	{
		if (ft_strcmp(key, list->key) == 0)
			return (list);
		list = list->next;
	}
	return (0);
}
