/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:31:53 by oakerkao          #+#    #+#             */
/*   Updated: 2023/05/11 12:50:48 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
/*char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (0);
	str = malloc(((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char)) + 1);
	if (!str)
		return (0);
	while (s1[i] != '\0')
	{
		str[j++] = s1[i++];
	}
	i = 0;
	while (s2[i] != '\0')
	{
		str[j++] = s2[i++];
	}
	str[j] = '\0';
	return (str);
}*/

t_list	*get_list(int size, va_list args)
{
	t_list	*lst;
	int		i;
	char	*str;

	i = 0;
	lst = NULL;
	while (i < size)
	{
		str = va_arg(args, char *);
		ft_lstadd_back(&lst, ft_lstnew(str));
		i++;
	}
	return (lst);
}

int	list_content_size(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i += ft_strlen(lst->content);
		lst = lst->next;
	}
	return (i);
}

char	*put_arr(t_list *lst, int len)
{
	char	*result;
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(len + 1);
	while (lst)
	{
		j = 0;
		str = lst->content;	
		while (str && str[j])
		{
			result[i] = str[j];
			i++;
			j++;
		}
		lst = lst->next;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strjoin(int size, ...)
{
	va_list	args;
	char	*result;
	t_list	*lst;
	int		len;
	
	lst = NULL;
	va_start(args, size);
	lst = get_list(size, args);
	len = list_content_size(lst);
	result = put_arr(lst, len);
	va_end(args);
	return (result);
}
