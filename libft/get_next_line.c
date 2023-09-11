/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 09:39:23 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/11 19:28:53 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*str_dup(char *str)
{
	char	*res_str;
	int		i;

	i = 0;
	res_str = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	while (str[i])
	{
		res_str[i] = str[i];
		i++;
	}
	res_str[i] = '\0';
	return (res_str);
}

char	*read_check(int fd, char *result)
{
	char	*str;
	int		ret;

	ret = 1;
	str = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!str)
		return (0);
	while (ret > 0)
	{
		ret = read(fd, str, BUFFER_SIZE);
		if (ret == 0 || (ret == -1 && !result))
			break ;
		if (ret == -1 && result)
		{
			free(result);
			result = NULL;
			break ;
		}
		str[ret] = '\0';
		result = str_res(result, str);
		if (ft_strchr(result, '\n'))
			break ;
	}
	free(str);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*result;
	char		*final;

	if (fd < 0 || fd == 1 || fd == 2 || BUFFER_SIZE <= 0)
		return (0);
	result = read_check(fd, result);
	if (!result)
		return (0);
	final = str_rem(result);
	result = str_save(result);
	return (final);
}
