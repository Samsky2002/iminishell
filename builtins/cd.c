/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 12:19:12 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/10 08:54:20 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	change_pwd(char *path, t_minishell *minishell)
{
	t_env	*current;
	char	*str;
	t_env	*env;

	env = minishell->env;
	str = getcwd(NULL, 0);
	current = get_node("PWD", env);
	if (str && current)
		current->value = str;
}

void	change_old_pwd(t_minishell *minishell)
{
	t_env	*old;
	t_env	*current;
	t_env	*env;

	env = minishell->env;
	old = get_node("OLDPWD", env);
	current = get_node("PWD", env);
	if (old && current)
		old->value = ft_strdup(current->value);
}

void	change_to_home(t_minishell *minishell)
{
	t_env	*home;
	t_env	*current;
	t_env	*env;

	env = minishell->env;
	change_old_pwd(minishell);
	home = get_node("HOME", env);
	current = get_node("PWD",env);
	if (home && current)
	{
		current->value = ft_strdup(home->value);
		chdir(home->value);
	}
	else
		printf("home not set\n");
	// check_leaks
}

void	cd(char *path, t_minishell *minishell)
{
	if (!path)
	{
		change_to_home(minishell);
		return ;
	}
	if (chdir(path) == -1)
	{
		minishell->mini_error = NO_SUCH_FILE;
		return ;
	}
	change_old_pwd(minishell);
	change_pwd(path, minishell);
}

// cd has a problem when you have multiple pipes
// maybe take the last path
