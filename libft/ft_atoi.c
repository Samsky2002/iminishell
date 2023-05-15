/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:35:35 by oakerkao          #+#    #+#             */
/*   Updated: 2022/10/31 16:42:28 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	atoi_con(const char *str, int i, int k)
{
	int	result;

	result = 0;
	if (str[i] <= '9' && str[i] >= '0')
	{
		while (str[i] == '0')
			i++;
		while (str[i] <= '9' && str[i] >= '0' && str[i])
		{
			result = (result * 10) + (str[i] - 48);
			i++;
		}
		if (str[k] == '-')
			result *= -1;
	}
	return (result);
}

int	ft_atoi(const char	*str)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' \
			|| str[i] == '\f' || str[i] == '\v' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			k = i;
		i++;
	}
	if (str[i] >= '0' && str[i] <= '9')
		return (atoi_con(str, i, k));
	return (0);
}
