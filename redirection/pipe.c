/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:53:54 by oakerkao          #+#    #+#             */
/*   Updated: 2023/05/03 18:48:07 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

int	piping(t_ast *head)
{
	int	fd[2];
	int	pid;

	if (head->left)
		piping(head->next);
	if (head->right)
		piping(head->right);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], 1);
		execve(path, head->left, NULL);
	}
	dup2(fd[1][0], 0);
}
