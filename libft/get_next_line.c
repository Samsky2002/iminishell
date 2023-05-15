/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:45:38 by oakerkao          #+#    #+#             */
/*   Updated: 2023/04/05 16:22:47 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*result[OPEN_MAX];
	char		*final;

	if (fd < 0 || fd == 1 || fd == 2 || BUFFER_SIZE <= 0)
		return (0);
	result[fd] = read_check(fd, result[fd]);
	if (!result[fd])
		return (0);
	final = str_rem(result[fd]);
	result[fd] = str_save(result[fd]);
	return (final);
}
