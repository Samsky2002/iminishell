/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:44:26 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/08 11:55:26 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*path_check(char *split, char *cmd)
{
	char	*result;
	char	*tmp;

	result = NULL;
	result = ft_strjoin(split, "/");
	tmp = ft_strjoin(result, cmd);
	free(result);
	result = tmp;
	if (!access(result, F_OK))
	{
		if (!access(result, X_OK))
			return (result);
		g_minishell.mini_error = PERMISSION_DENIED_PROG;
	}
	free(result);
	return (0);
}

char	*program_check(char *cmd)
{
	if (!access(cmd, F_OK))
	{
		if (!access(cmd, X_OK))
			return (cmd);
		g_minishell.mini_error = PERMISSION_DENIED_PROG;
		return (cmd);
	}
	g_minishell.mini_error = NO_SUCH_PROGRAM;
	return (0);
}

char	*path_getter(char *cmd)
{
	t_env	*list;
	char	**split;
	int		i;

	i = 0;
	list = get_node("PATH");
	if (!list)
	{
		g_minishell.mini_error = NO_SUCH_PROGRAM;
		return (0);
	}
	else if (!cmd || !*cmd)
	{
		g_minishell.mini_error = CMD_NOT_FOUND;
		return (0);
	}
	if (ft_strchr(cmd, '/'))
		return (program_check(cmd));
	split = ft_split(list->value, ':');
	while (split[i])
	{
		if (path_check(*(split + i), cmd))
			return(path_check(*(split + i), cmd));
		i++;
	}
	if (g_minishell.mini_error != PERMISSION_DENIED_PROG)
		g_minishell.mini_error = CMD_NOT_FOUND;
	free_twod_array(split);
	return (0);
}

// you can check if no such file for program with checking for /
// you have to check the program only if he has /
