/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:07:47 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/13 11:09:16 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	exec_redirect_list_clear(t_exec_redirect *redirect)
{
	t_exec_redirect	*head;

	if (!redirect)
		return ;
	head = redirect;
	while (head)
	{
		head = redirect->next;
		free_twod_array(redirect->list);
		free(redirect);
		redirect = head;
	}
}

void	exec_list_clear(t_exec *exec)
{
	t_exec	*head;

	if (!exec)
		return ;
	head = exec;
	while (head)
	{
		head = exec->next;
		free_twod_array(exec->args);
		exec_redirect_list_clear(exec->redirect);
		free(exec);
		exec = head;
	}
}

int	exec_list_count(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec)
	{
		i++;
		exec = exec->next;
	}
	return (i);
}
