/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:26:19 by oakerkao          #+#    #+#             */
/*   Updated: 2023/05/02 19:52:21 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "redirection.h"

int	infile(char *file)
{
	int	fd;

	fd = open(file, RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("error\n");	
	}
	return (fd);
}
