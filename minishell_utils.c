/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:54:33 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/13 11:36:01 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*char_join_help(char *str, char c)
{
	char	*result;

	if (!str && c == '\0')
	{
		result = malloc(1);
		result[0] = '\0';
		return (result);
	}
	else if (!str)
	{
		result = malloc(2);
		result[0] = c;
		result[1] = '\0';
		return (result);
	}
	return (0);
}

char	*char_join(char *str, char c)
{
	char	*result;
	int		len;
	int		i;
	char	*help;

	i = 0;
	help = char_join_help(str, c);
	if (help)
		return (help);
	if (c == '\0')
		return (str);
	len = ft_strlen(str);
	result = malloc(len + 2);
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = c;
	result[i + 1] = '\0';
	free(str);
	return (result);
}

void	free_twod_array(char **arr)
{
	char	**tmp;

	tmp = arr;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(arr);
}

int	put_twod_size(t_list *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		if (lst->content)
			len++;
		lst = lst->next;
	}
	return (len);
}

char	**put_twod_array(t_list **lst)
{
	int		len;
	char	**arr;
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *lst;
	len = put_twod_size(tmp);
	arr = malloc((len + 1) * sizeof(char *));
	while (tmp)
	{
		if (tmp->content)
		{
			arr[i] = ft_strdup(tmp->content);
			i++;
		}
		tmp = tmp->next;
	}
	arr[i] = NULL;
	ft_lstclear(lst, free);
	return (arr);
}
