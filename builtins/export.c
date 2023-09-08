/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:16:20 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/06 16:41:59 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	export_list(void)
{
	t_env	*list;

	list = g_minishell.list;
	while (list)
	{
		if (list->value != NULL && (ft_strcmp(list->key, "_") != 0))
			printf("declare -x %s=\"%s\"\n", list->key, list->value);
		else if (list->value == NULL && (ft_strcmp(list->key, "_") != 0))
			printf("declare -x %s\n", list->key);
		list = list->next;
	}
}

int	check_key(char *str)
{
	int	i;

	i = 1;
	if ((str[0] < 'a' || str[0] > 'z') && (str[0] < 'A' || str[0] > 'Z') \
			&& str[0] != '_')
	{
		return (0);
	}
	while (str[i] && str[i] != '=')
	{
		if ((str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z') && \
				(str[i] < '0' || str[i] > '9') && (str[i] != '_'))
		{
			printf("error\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	export(char **argv)
{
	int		i;
	t_env	*tmp;

	i = 1;
	if (!argv[i])
	{
		export_list();
		return ;
	}
	while (argv[i])
	{
		if (check_key(argv[i]) == 0)
		{
			printf("error\n");
		}
		else if (get_node(get_key(argv[i])))
		{
			tmp = get_node(get_key(argv[i]));
			if (get_value(argv[i]))
				tmp->value = get_value(argv[i]);
		}
		else
		{
			add_node(&g_minishell.list, new_node(get_key(argv[i]), get_value(argv[i])));
		}
		i++;
	}
}
