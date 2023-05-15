/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:27:51 by oakerkao          #+#    #+#             */
/*   Updated: 2023/05/02 19:29:48 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

int	outfile(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_RDONLY, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("error\n", 2);
	}
	return (fd);
}
