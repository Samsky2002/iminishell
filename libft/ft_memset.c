/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:01:48 by oakerkao          #+#    #+#             */
/*   Updated: 2022/10/22 11:05:36 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	z;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)b;
	z = (unsigned char)c;
	while (i < len)
	{
		str[i] = z;
		i++;
	}
	return (b);
}
