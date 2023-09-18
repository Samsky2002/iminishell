/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:46:45 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/16 10:23:21 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_expansion(t_list **lst, t_minishell *minishell, \
		char *str)
{
	t_list	*tmp;
	int		i;
	char	quotes;

	i = 0;
	quotes = 0;
	ft_lstadd_back(lst, ft_lstnew(NULL));
	tmp = *lst;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && !quotes)
			quotes = str[i];
		else if (str[i] == quotes && quotes)
			quotes = 0;
		else if (str[i] == '$' && !quotes)
			i += expand_quoted_variable(&tmp, str, minishell);
		else
			tmp->content = char_join(tmp->content, str[i]);
		if (!str[i])
			break ;
		i++;
	}
}
