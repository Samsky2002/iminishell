/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:48:54 by oakerkao          #+#    #+#             */
/*   Updated: 2022/10/28 10:01:20 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_str;
	unsigned char	*s2_str;
	size_t			i;

	i = 0;
	s1_str = (unsigned char *)s1;
	s2_str = (unsigned char *)s2;
	while (i < n)
	{
		if (s1_str[i] != s2_str[i] && i < n)
			return (s1_str[i] - s2_str[i]);
		i++;
	}
	return (0);
}
