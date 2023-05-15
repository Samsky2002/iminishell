/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:31:12 by oakerkao          #+#    #+#             */
/*   Updated: 2022/10/31 16:45:40 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_nb(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		count = 1;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*print_char(long nb, int count, int sign)
{
	char	*str;
	long	a;
	int		i;

	i = 0;
	str = (char *)malloc((count + 1) * sizeof(char));
	if (!str)
		return (0);
	while (nb > 0)
	{
		a = nb;
		nb /= 10;
		a %= 10;
		a += 48;
		str[i] = (char)a;
		i++;
	}
	if (sign == 1)
	{
		str[i] = '-';
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*nb_zero(long nb, char	*fstr)
{
	int	i;

	i = 0;
	if (nb == 0)
	{
		nb %= 10;
		nb += 48;
		fstr[i] = nb;
		fstr[i + 1] = '\0';
	}
	return (fstr);
}

static void	nb_swap(int len, char *fstr)
{
	char	swap;
	int		i;

	i = 0;
	while (len >= 0 && len > i)
	{
		swap = fstr[i];
		fstr[i] = fstr[len];
		fstr[len] = swap;
		i++;
		len--;
	}
}

char	*ft_itoa(int n)
{
	int		sign;
	char	*fstr;
	int		len;
	long	nb;
	int		count;

	nb = n;
	count = count_nb(nb);
	sign = 0;
	if (nb < 0)
	{
		nb *= -1;
		sign = 1;
	}
	fstr = print_char(nb, count, sign);
	if (!fstr)
		return (0);
	if (nb == 0)
		return (nb_zero(nb, fstr));
	len = ft_strlen(fstr) - 1;
	nb_swap(len, fstr);
	return (fstr);
}
