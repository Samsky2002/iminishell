/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:40:26 by oakerkao          #+#    #+#             */
/*   Updated: 2022/10/31 16:05:11 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	*str;
	unsigned char	k;

	i = ft_strlen(s);
	k = (unsigned char)c;
	str = (unsigned char *)s;
	while (i > 0 && str[i] != k)
		i--;
	if (str[i] == k)
		return ((char *)(str + i));
	return (0);
}
