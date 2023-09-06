/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:44:26 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/06 15:08:26 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*path_getter(char *cmd)
{
	t_env	*list;
	char	**split;
	char	*result;
	char	*tmp;
	int		i;

	i = 0;
	result = NULL;
	list = get_node("PATH");
	if (!list || !cmd)
		return (0);
	split = ft_split(list->value, ':');
	while (split[i])
	{
		result = ft_strjoin(split[i], "/");
		tmp = ft_strjoin(result, cmd);
		free(result);
		result = tmp;
		if (!access(result, F_OK))
		{
			//check_exec_permission
			return (result);
		}
		free(result);
		i++;
	}
	free_twod_array(split);
	return (0);
}
