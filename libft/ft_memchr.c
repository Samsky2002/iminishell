/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:49:27 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/11 17:40:15 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	k;
	unsigned char	*str;

	i = 0;
	k = (unsigned char)c;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == k && i < n)
		{
			return (str + i);
		}
		i++;
	}
	return (0);
}
