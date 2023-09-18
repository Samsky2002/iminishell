/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:01:26 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/14 10:47:12 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	check_flag(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] == '-')
		i++;
	else
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo_help(int flag)
{
	if (flag == 0)
		printf("\n");
}

void	echo(char **cmd)
{
	int	i;
	int	flag;
	int	other;

	i = 1;
	flag = check_flag(cmd[1]);
	if (flag == 1)
	{
		while (cmd && cmd[i])
		{
			other = check_flag(cmd[i]);
			if (other == 1)
				i++;
			else
				break ;
		}
	}
	while (cmd && cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd + i + 1 && cmd[i + 1])
			printf(" ");
		i++;
	}
	echo_help(flag);
}
