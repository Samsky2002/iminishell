/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:07:47 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/03 17:01:38 by oakerkao         ###   ########.fr       */
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

void	print_exec()
{
	t_exec	*exec;

	exec = g_minishell.exec;
	while (exec)
	{
		printf("<<<<<<<<<<<<<NODE>>>>>>>>>>>>>>>>\n");
		printf("-----------ARGS------------\n");
		while (*exec->args)	
		{
			printf("%s\n", *exec->args);	
			exec->args++;
		}
		printf("-----------ARGS------------\n");
		printf("-----------REDIRECT------------\n");
		while (exec->redirect)
		{
			while (*exec->redirect->list)
			{
				printf("TYPE---->  ");	
				printf("%s\n", *exec->redirect->list);
				find_type(exec->redirect->type);
				exec->redirect->list++;
			}
			exec->redirect = exec->redirect->next;
		}
		exec = exec->next;
		printf("-----------REDIRECT------------\n");
		printf("<<<<<<<<<<<<<<END_NODE>>>>>>>>>>>>>\n\n\n");
	}
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
