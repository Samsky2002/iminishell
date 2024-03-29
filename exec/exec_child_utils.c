/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:44:26 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/13 11:22:27 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	twod_array_size(char **arr)
{
	int		i;

	i = 0;
	while (arr && arr[i])
	{
		i++;
	}
	return (i);
}

char	*path_check(char *split, char *cmd, t_minishell *minishell)
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
		minishell->mini_error = PERMISSION_DENIED_PROG;
	}
	free(result);
	return (0);
}

char	*program_check(char *cmd, t_minishell *minishell)
{
	if (!access(cmd, F_OK))
	{
		if (!access(cmd, X_OK))
			return (cmd);
		minishell->mini_error = PERMISSION_DENIED_PROG;
		return (cmd);
	}
	minishell->mini_error = NO_SUCH_PROGRAM;
	return (0);
}

int	path_getter_check(char *cmd, t_env *list, t_minishell *minishell)
{
	if (!list)
	{
		minishell->mini_error = NO_SUCH_PROGRAM;
		return (0);
	}
	else if (!cmd)
		return (0);
	else if (!*cmd)
	{
		minishell->mini_error = CMD_NOT_FOUND;
		return (0);
	}
	return (1);
}

char	*path_getter(char *cmd, t_minishell *minishell)
{
	t_env	*list;
	char	**split;
	int		i;

	i = 0;
	list = get_node("PATH", minishell->env);
	if (path_getter_check(cmd, list, minishell) == 0)
		return (0);
	if (ft_strchr(cmd, '/'))
		return (program_check(cmd, minishell));
	split = ft_split(list->value, ':');
	while (split[i])
	{
		if (path_check(*(split + i), cmd, minishell))
			return (path_check(*(split + i), cmd, minishell));
		i++;
	}
	if (minishell->mini_error != PERMISSION_DENIED_PROG)
		minishell->mini_error = CMD_NOT_FOUND;
	free_twod_array(split);
	return (0);
}
