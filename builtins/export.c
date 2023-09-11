/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:16:20 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/11 13:21:15 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	export_list(t_minishell *minishell)
{
	t_env	*list;

	list = minishell->env;
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
			return (0);
		}
		i++;
	}
	return (1);
}

void	export(char **argv, t_minishell *minishell)
{
	int		i;
	t_env	*tmp;

	i = 1;
	if (!argv[i])
	{
		export_list(minishell);
		return ;
	}
	while (argv[i])
	{
		if (check_key(argv[i]) == 0)
		{
			minishell->mini_error = E_NOT_VALID;
			exec_error_msg(minishell);
			exec_error(minishell);
		}
		else if (get_node(get_key(argv[i]), minishell->env))
		{
			tmp = get_node(get_key(argv[i]), minishell->env);
			if (get_value(argv[i]))
				tmp->value = get_value(argv[i]);
		}
		else
			add_node(&minishell->env, new_node(get_key(argv[i]), get_value(argv[i])));
		i++;
	}
}
