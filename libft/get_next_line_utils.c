/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:46:00 by oakerkao          #+#    #+#             */
/*   Updated: 2023/04/06 01:02:09 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*str_res(char *str1, char *str2)
{
	char	*res_str;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (str1 == NULL && str2 != NULL)
		return (str_dup(str2));
	else if (str1 != NULL && str2 != NULL)
	{
		res_str = (char *)malloc((ft_strlen(str1) + \
					ft_strlen(str2) + 1) * sizeof(char));
		if (!res_str)
			return (0);
		while (str1[j])
			res_str[i++] = str1[j++];
		j = 0;
		while (str2[j])
			res_str[i++] = str2[j++];
		res_str[i] = '\0';
		free(str1);
	}
	else
		return (0);
	return (res_str);
}

char	*str_rem(char *str)
{
	char	*rem_str;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	rem_str = (char *)malloc((i + 1) * sizeof(char));
	if (!rem_str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		rem_str[i] = str[i];
		i++;
	}
	if (str[i] && str[i] == '\n')
	{
		rem_str[i] = str[i];
		rem_str[++i] = '\0';
	}
	else
		rem_str[i] = '\0';
	return (rem_str);
}

char	*str_save(char	*str)
{
	char	*save_str;
	int		i;
	int		j;
	int		len;

	j = 0;
	len = ft_strlen(str);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	if (str[i])
	{
		save_str = malloc((len - i) + 1);
		if (!save_str)
			return (0);
		while (str[i])
			save_str[j++] = str[i++];
		save_str[j] = '\0';
		free(str);
		return (save_str);
	}
	free(str);
	return (0);
}
