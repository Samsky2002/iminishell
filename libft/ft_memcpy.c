/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:15:40 by oakerkao          #+#    #+#             */
/*   Updated: 2022/10/22 12:37:27 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy( void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*str_src;
	char	*str_dst;

	i = 0;
	str_src = (char *)src;
	str_dst = (char *)dst;
	if (str_src == 0 && str_dst == 0)
		return (0);
	while (i < n)
	{
		str_dst[i] = str_src[i];
		i++;
	}
	return (dst);
}
