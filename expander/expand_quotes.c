/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:04:52 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/14 13:36:29 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_quoted_variable(t_list **tmp, \
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
