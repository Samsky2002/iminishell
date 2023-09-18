/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 13:23:47 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/15 12:32:28 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *str)
{
	int		i;
	char	*result;

	i = 1;
	if (!str || !*str)
		return (0);
	if (str[0] == '?')
		return (ft_strdup("?"));
	else if (str && str[0] && !((str[0] >= 'a' && str[0] <= 'z') || \
				(str[0] >= 'A' && str[0] <= 'Z') || \
				(str[0] == '_')))
		return (0);
	while (str[i] && ((str[i] >= '0' && str[i] != '9') || \
				(str[i] >= 'a' && str[i] <= 'z') || \
				(str[i] >= 'A' && str[i] <= 'Z') || \
				str[i] == '_'))
		i++;
	result = malloc(i + 1);
	ft_strlcpy(result, str, i + 1);
	return (result);
}

int	has_space(char *str, int type)
{
	int	len;
	int	i;

	i = 0;
	if (!str || !*str)
		return (-1);
	len = ft_strlen(str);
	if (type == 0)
	{
		while (str[i] == ' ')
			i++;
		if (i == len)
			return (1);
	}
	if (type == -1)
	{
		if (*str == ' ')
			return (1);
	}
	else if (type == 1)
	{
		if (str[len - 1] == ' ')
			return (1);
	}
	return (0);
}

void	expand_exit_status(t_list **tmp, t_minishell *minishell)
{
	char	*temp;
	char	*itoa_temp;

	itoa_temp = ft_itoa(minishell->exit_s);
	if ((*tmp)->content)
	{
		temp = ft_strjoin((*tmp)->content, itoa_temp);
		free((*tmp)->content);
		(*tmp)->content = temp;
	}
	else
		(*tmp)->content = ft_strdup(itoa_temp);
	free(itoa_temp);
}
