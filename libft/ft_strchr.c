/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:08:25 by oakerkao          #+#    #+#             */
/*   Updated: 2023/01/25 19:13:56 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	*str;
	unsigned char	k;

	i = 0;
	k = (unsigned char)c;
	str = (unsigned char *)s;
	while (str[i] != k && str[i])
		i++;
	if (str[i] == k)
		return ((char *)(str + i));
	return (0);
}
