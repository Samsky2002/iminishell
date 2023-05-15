/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:01:26 by oakerkao          #+#    #+#             */
/*   Updated: 2023/04/24 13:06:14 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	echo(char **cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (cmd && cmd[1] && ft_strncmp(cmd[1], "-n", ft_strlen(cmd[1])) == 0)
	{
		i = 2;
		flag = 1;
	}
	while (cmd && cmd[i])
	{
		printf("%s", cmd[i]);
		i++;
	}
	if (flag == 0)
		printf("\n");
}
