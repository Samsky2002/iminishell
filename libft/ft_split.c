/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:58:46 by oakerkao          #+#    #+#             */
/*   Updated: 2022/10/31 15:58:41 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != c && str[i])
		{
			while (str[i] != c && str[i])
			{
				i++;
			}
			count++;
		}
	}
	return (count);
}

static int	count_char(char const *str, char c, int i)
{
	int	count;

	count = 0;
	while (str[i] != c && str[i])
	{
		i++;
		count++;
	}
	return (count);
}

static void	cpy(char **str, char const *s, char c, int count)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	j = 0;
	while (i < count)
	{
		j = 0;
		while (s[k] == c && s[k])
			k++;
		while (s[k] != c && s[k])
		{
			str[i][j] = s[k];
			k++;
			j++;
		}
		str[i][j] = '\0';
		i++;
	}	
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;
	int		k;
	int		count;

	count = count_word(s, c);
	i = 0;
	j = 0;
	k = 0;
	str = malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!str)
		return (0);
	while (i < count_word(s, c))
	{
		while (s[j] == c && s[j])
			j++;
		str[i] = malloc((count_char(s, c, j) + 1) * sizeof(char));
		j += count_char(s, c, j);
		i++;
	}
	cpy(str, s, c, count);
	str[i] = 0;
	return (str);
}
