/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:51:47 by oakerkao          #+#    #+#             */
/*   Updated: 2023/05/03 12:29:12 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

int	here_doc(char *delimiter, int fd)
{
	char	*red;

	while (1)
	{
		red = readline("> ");	
		if (ft_strcmp(red, delimiter) == 0)
			break ;
		ft_putstr_fd(red, fd);
		ft_putstr_fd("\n", fd);
	}
	return (fd);
}

int main()
{
	char *arr[] = {"cat", NULL};
	int		fd[2];

	pipe(fd);
	here_doc("hi", fd[1]);
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
	execve("/bin/cat", arr, NULL);
}
