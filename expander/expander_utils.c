/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 13:23:47 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/03 15:17:06 by oakerkao         ###   ########.fr       */
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
	if (str && str[0] && !((str[0] >= 'a' && str[0] <= 'z') || \
				(str[0] >= 'A' && str[0] <= 'Z') || \
				(str[0] == '_')))
	{
		return (0);
	}
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
	/*i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}*/
	ft_lstclear(lst, free);
	return (arr);
}

void	expander_init(t_list **lst, char *quotes, int *i)
{
	*i = 0;
	*quotes = 0;
	*lst = NULL;
	ft_lstadd_back(lst, ft_lstnew(NULL));
}
