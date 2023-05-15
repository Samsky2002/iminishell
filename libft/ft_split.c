/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:58:46 by oakerkao          #+#    #+#             */
/*   Updated: 2023/05/14 17:02:47 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

char	*join_char(char	*str, char c)
{
	int		i;
	int		len;
	char	*result;

	len = 0;
	i = 0;
	if (str)
		len = ft_strlen(str);
	result = malloc(len + 2);	
	while (str && str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = c;
	result[i + 1] = '\0';
	if (str)
		free(str);
	return (result);
}

char	**put_twod_array(t_list *lst)
{
	int		len;
	char	**arr;
	int		i;

	i = 0;
	if (!lst || lst->content == NULL)
		return (0);
	len = ft_lstsize(lst);
	arr = malloc((len + 1) * sizeof(char *));
	while (lst)
	{
		arr[i] = ft_strdup(lst->content);
		lst = lst->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char *str, char c)
{
	int		i;
	int		quotes;
	char	*result;
	t_list	*lst;
	char	**arr;
	
	i = 0;
	quotes = 0;
	result = NULL;
	lst	= NULL;
	while (str && str[i])
	{
		if (is_quote(str[i]) && quotes == 0)
			quotes = str[i];
		else if (str[i] == quotes && quotes)
			quotes = 0;
		else if (quotes || (str[i] != c && quotes == 0))
				result = join_char(result, str[i]);
		if ((str[i] == c && quotes == 0 && result) || str[i + 1] == '\0')
		{
			ft_lstadd_back(&lst, ft_lstnew(result));
			result = NULL;
		}
		i++;
	}
	arr = put_twod_array(lst);
	return (arr);
}
