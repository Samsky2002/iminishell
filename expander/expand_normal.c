/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:05:04 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/14 18:36:57 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_next(t_list **lst, t_list **tmp)
{
	ft_lstadd_back(lst, ft_lstnew(NULL));
	*tmp = (*tmp)->next;
}

void	add_split(t_list **lst, t_list **tmp, char **splited)
{
	int		i;
	char	*temp;

	i = 0;
	while (splited && *splited)
	{
		if ((*tmp)->content)
		{
			temp = ft_strjoin((*tmp)->content, *splited);
			free((*tmp)->content);
			(*tmp)->content = temp;
		}
		else
			(*tmp)->content = ft_strdup(*splited);
		if (*(splited + 1))
			go_next(lst, tmp);
		splited++;
	}
}

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
		if ((*tmp)->content)
			go_next(lst, tmp);
	}
	if (has_space(node->value, 0))
	{
		if ((*tmp)->content)
			go_next(lst, tmp);
	}
	add_split(lst, tmp, splited);
	if (has_space(node->value, 1) && !has_space(node->value, 0))
		go_next(lst, tmp);
	free_twod_array(splited_tmp);
}

int	expand_variable(t_list **lst, t_list **tmp, \
		char *str, t_minishell *minishell)
{
	char	*var;
	char	**splited;
	t_env	*node;
	size_t	len;
	char	**splited_tmp;

	splited = NULL;
	splited_tmp = NULL;
	var = get_var_name(str + 1);
	if (!var)
		return (1);
	len = ft_strlen(var);
	str += len + 1;
	if (ft_strcmp(var, "?") == 0)
		expand_exit_status(tmp, minishell);
	node = get_node(var, minishell->env);
	if (node && node->value && node->value[0])
		expand_variable_helper(node, lst, tmp);
	free(var);
	return (len);
}
