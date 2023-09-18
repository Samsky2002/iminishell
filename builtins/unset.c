/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:56:37 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/14 17:33:52 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	remove_node(char *key, t_minishell *minishell)
{
	t_env	*current;
	t_env	*prev;

	current = minishell->env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0 && ft_strcmp(current->key, "_"))
		{
			if (prev == NULL)
				minishell->env = minishell->env->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

void	unset(char **args, t_minishell *minishell)
{
	int		i;
	char	*str;

	i = 1;
	if (!*args)
		return ;
	while (args[i])
	{
		if (check_key(args[i]) == 0)
		{
			minishell->mini_error = U_NOT_VALID;
			exec_error(minishell);
			return ;
		}
		else if (ft_strchr(args[i], '='))
			return ;
		else
		{
			str = get_key(args[i]);
			remove_node(str, minishell);
			free(str);
		}
		i++;
	}
}
