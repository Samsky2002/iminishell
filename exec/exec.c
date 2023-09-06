/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:57:28 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/06 15:25:04 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(void)
{
	t_fd	*fd;
	exec_prep();
	here_doc_traverse();
	piping();
	fd = g_minishell.here_doc;
	while (fd)
	{
		close(fd->fd);
		fd = fd->next;
	}
	/*tasty*/
	//exec_child(&ctx);
	//print_exec();
	//
}
