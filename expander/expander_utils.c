/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 13:23:47 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/09 10:30:58 by oakerkao         ###   ########.fr       */
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

void	expander_init(t_list **lst, char *quotes, int *i, t_list **tmp)
{
	*i = -1;
	*quotes = 0;
	*lst = NULL;
	ft_lstadd_back(lst, ft_lstnew(NULL));
	*tmp = *lst;
}

/*void	expand_variable_helper(t_env *node, t_list **lst, t_list **tmp)
{
	char	**splited;
	char	**splited_tmp;

	splited = NULL;
	splited_tmp = NULL;
	if (node->value && node->value[0])
	{
		splited = ft_split(node->value, ' ');
		splited_tmp = splited;
	}
	if ((*tmp)->content && splited && has_space(node->value, -1) == 0)
		splited += left_space_expand_variable(tmp, splited);
	add_split(lst, tmp, splited);
	if (has_space(node->value, 0))
		return ;
	if (has_space(node->value, 1) && node->value && node->value[0])
	{
		ft_lstadd_back(lst, ft_lstnew(NULL));
		(*tmp) = (*tmp)->next;
	}
	if (splited_tmp)
		free_twod_array(splited_tmp);
}*/

void	expand_variable_helper(t_env *node, t_list **lst, t_list **tmp)
{
	char	**splited;
	char	**splited_tmp;

	splited = NULL;
	splited_tmp = NULL;
	if (node->value && node->value[0])
	{
		splited = ft_split(node->value, ' ');
		splited_tmp = splited;
	}
	if (has_space(node->value, -1) && !has_space(node->value, 0))
	{
		ft_lstadd_back(lst, ft_lstnew(NULL));
		(*tmp) = (*tmp)->next;
	}
	add_split(lst, tmp, splited);
	if (has_space(node->value, 1) && !has_space(node->value, 0))
	{
		ft_lstadd_back(lst, ft_lstnew(NULL));
		(*tmp) = (*tmp)->next;
	}
}
