/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:04:54 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/03 14:53:30 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_split(t_list **lst, t_list **tmp, char **splited)
{
	while (splited && *splited)
	{
		ft_lstadd_back(lst, ft_lstnew(NULL));
		(*tmp) = (*tmp)->next;
		(*tmp)->content = ft_strdup(*splited);
		splited++;
	}
}

int	expand_variable(t_list **lst, t_list **tmp, char *str)
{
	char	*var;
	char	**splited;
	t_env	*node;

	splited = NULL;
	var = get_var_name(str + 1);
	node = get_node(var);
	if (node)
	{
		if (node->value && node->value[0])
			splited = ft_split(node->value, ' ');
		if ((*tmp)->content && splited && has_space(node->value, -1) == 0)
		{
			(*tmp)->content = ft_strjoin((*tmp)->content, *splited);
			splited++;
		}
		add_split(lst, tmp, splited);
		if (has_space(node->value, 1))
		{
			ft_lstadd_back(lst, ft_lstnew(NULL));
			(*tmp) = (*tmp)->next;
		}
	}
	return (ft_strlen(var));
}

int	expand_quoted_variable(t_list **lst, t_list **tmp, char *str)
{
	char	*var;
	char	**splited;
	t_env	*node;

	var = get_var_name(str + 1);
	node = get_node(var);
	if (node)
	{
		if ((*tmp)->content)
			(*tmp)->content = ft_strjoin((*tmp)->content, node->value);
		else
			(*tmp)->content = ft_strdup(node->value);
	}
	return (ft_strlen(var));
}

char	**expander(char *str)
{
	int		i;
	char	quotes;
	t_list	*lst;
	t_list	*tmp;

	expander_init(&lst, &quotes, &i);
	tmp = lst;
	while (str && str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && !quotes)
		{
			tmp->content = char_join(tmp->content, '\0');
			quotes = str[i];
		}
		else if (str[i] == quotes)
			quotes = 0;
		else if (str[i] == '$' && quotes == 0)
			i += expand_variable(&lst, &tmp, str + i);
		else if (str[i] == '$' && quotes == '"')
			i += expand_quoted_variable(&lst, &tmp, str + i);
		else
			tmp->content = char_join(tmp->content, str[i]);
		i++;
	}
	return (put_twod_array(&lst));
}

void	expanded(void)
{
	t_node	*node;

	node = g_minishell.node;
	while (node)
	{
		while (node->args)
		{
			expander(node->args->arg);
			node->args = node->args->next;
		}
		node = node->next;
	}
}
