/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:04:54 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/11 10:08:24 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	left_space_expand_variable(t_list **tmp, char **splited)
{
	char	*temp;
	char	**tmp_splited;

	tmp_splited = splited;
	temp = ft_strjoin((*tmp)->content, *splited);
	if ((*tmp)->content)
		free((*tmp)->content);
	(*tmp)->content = temp;
	splited++;
	return (1);
}

void	expand_exit_status(t_list **tmp, t_minishell *minishell)
{
	char	*temp;

	if ((*tmp)->content)
	{
		temp = ft_strjoin((*tmp)->content, ft_itoa(minishell->exit_s));
		free((*tmp)->content);
		(*tmp)->content = temp;
	}
	else
		(*tmp)->content = ft_strdup(ft_itoa(minishell->exit_s));
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
	if (ft_strcmp(var, "?") == 0)
		expand_exit_status(tmp, minishell);
	node = get_node(var, minishell->env);
	len = ft_strlen(var);
	if (node && node->value && node->value[0])
		expand_variable_helper(node, lst, tmp);
	free(var);
	return (len);
}

int	expand_quoted_variable(t_list **lst, t_list **tmp, \
		char *str, t_minishell *minishell)
{
	char	*var;
	t_env	*node;
	int		len;
	char	*temp;

	var = get_var_name(str + 1);
	if (!var)
		return (1);
	if (ft_strcmp(var, "?") == 0)
		expand_exit_status(tmp, minishell);
	node = get_node(var, minishell->env);
	len = ft_strlen(var);
	if (node)
	{
		if ((*tmp)->content)
		{
			temp = ft_strjoin((*tmp)->content, node->value);
			free((*tmp)->content);
			(*tmp)->content = temp;
		}
		else
			(*tmp)->content = ft_strdup(node->value);
	}
	free(var);
	return (len);
}

char	**expander(char *str, t_minishell *minishell)
{
	int		i;
	char	quotes;
	t_list	*lst;
	t_list	*tmp;

	expander_init(&lst, &quotes, &i, &tmp);
	while (str && str[++i])
	{
		if ((str[i] == '\'' || str[i] == '"') && !quotes)
		{
			tmp->content = char_join(tmp->content, '\0');
			quotes = str[i];
		}
		else if (str[i] == quotes)
			quotes = 0;
		else if (str[i] == '$' && quotes == 0)
			i += expand_variable(&lst, &tmp, str + i, minishell);
		else if (str[i] == '$' && quotes == '"')
			i += expand_quoted_variable(&lst, &tmp, str + i, minishell);
		else
			tmp->content = char_join(tmp->content, str[i]);
		if (!str[i])
			break ;
	}
	return (put_twod_array(&lst));
}
