/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:04:54 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/14 16:24:14 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander_init(t_list **lst, char *quotes, int *i, t_list **tmp)
{
	*i = 0;
	*quotes = 0;
	ft_lstadd_back(lst, ft_lstnew(NULL));
	*tmp = ft_lstlast(*lst);
}

void	expander(t_list **lst, char *str, t_minishell *minishell)
{
	int		i;
	char	quotes;
	t_list	*tmp;

	expander_init(lst, &quotes, &i, &tmp);
	i = 0;
	while ((quotes || str[i] != ' ') && str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && !quotes)
		{
			tmp->content = char_join(tmp->content, '\0');
			quotes = str[i];
		}
		else if (str[i] == quotes)
			quotes = 0;
		else if (str[i] == '$' && quotes == 0)
			i += expand_variable(lst, &tmp, str + i, minishell);
		else if (str[i] == '$' && quotes == '"')
			i += expand_quoted_variable(&tmp, str + i, minishell);
		else
			tmp->content = char_join(tmp->content, str[i]);
		if (!str[i])
			break ;
		i++;
	}
}
