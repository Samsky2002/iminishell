/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:16:20 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/14 11:22:05 by oakerkao         ###   ########.fr       */
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

void	value_changer(t_minishell *minishell, char *key, \
		char *str)
{
	t_env	*tmp;
	char	*value;

	tmp = get_node(key, minishell->env);
	value = get_value(str);
	if (value)
	{
		if (tmp->value)
			free(tmp->value);
		tmp->value = value;
	}
}

void	not_valid_export(t_minishell *minishell)
{
	minishell->mini_error = E_NOT_VALID;
	exec_error_msg(minishell);
	exec_error(minishell);
}

void	export(char **argv, t_minishell *minishell)
{
	int		i;
	char	*key;

	i = 1;
	if (!argv[i])
	{
		export_list(minishell);
		return ;
	}
	while (argv[i])
	{
		key = get_key(argv[i]);
		if (check_key(argv[i]) == 0)
			not_valid_export(minishell);
		else if (get_node(key, minishell->env))
			value_changer(minishell, key, argv[i]);
		else
			add_node(&minishell->env, new_node(get_key(argv[i]), \
						get_value(argv[i])));
		free(key);
		i++;
	}
}
