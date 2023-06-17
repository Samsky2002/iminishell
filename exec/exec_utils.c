/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:07:47 by oakerkao          #+#    #+#             */
/*   Updated: 2023/06/17 11:15:05 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_exec	*new_exec(char **arr, t_exec_redirect *redirect)
{
	t_exec	*new;

	new = malloc(sizeof(t_exec));
	new->args = arr;
	new->redirect = redirect;
	new->next = NULL;
	return (new);
}

void	add_exec(t_exec **exec, t_exec *new)
{
	t_exec	*head;

	if (!*exec)
	{
		*exec = new;
		return ;	
	}
	head = *exec;
	while (head->next)
		head = head->next;
	head->next = new;
}
