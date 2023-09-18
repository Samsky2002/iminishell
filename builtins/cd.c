/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 12:19:12 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/15 12:13:48 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	change_pwd(t_minishell *minishell)
{
	t_env	*current;
	char	*str;
	t_env	*env;

	env = minishell->env;
	str = getcwd(NULL, 0);
	current = get_node("PWD", env);
	if (str && current)
		current->value = str;
	else
		free(str);
}

void	change_old_pwd(t_minishell *minishell, char *str)
{
	t_env	*old;
	t_env	*env;

	env = minishell->env;
	old = get_node("OLDPWD", env);
	if (!old)
		add_node(&minishell->env, new_node(ft_strdup("OLDPWD"), str));
	else if (old)
	{
		if (old->value)
			free(old->value);
		old->value = str;
	}
}

void	change_to_home(t_minishell *minishell, char *str)
{
	t_env	*home;
	t_env	*env;

	env = minishell->env;
	change_old_pwd(minishell, str);
	home = get_node("HOME", env);
	if (home)
	{
		chdir(home->value);
		change_pwd(minishell);
	}
	else
		minishell->mini_error = HOME_NOT_SET;
}

void	cd(char *path, t_minishell *minishell)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (!path)
	{
		change_to_home(minishell, str);
		return ;
	}
	else
	{
		if (chdir(path) == -1)
		{
			minishell->mini_error = NO_SUCH_FILE;
			return ;
		}
		change_old_pwd(minishell, str);
		change_pwd(minishell);
	}
}
