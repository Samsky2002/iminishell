/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:16:29 by oakerkao          #+#    #+#             */
/*   Updated: 2023/05/02 19:28:17 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

int	append_file(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_RDONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("error\n", 2);	
	}
	return (fd);
}
