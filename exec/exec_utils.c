/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:07:47 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/03 16:07:48 by oakerkao         ###   ########.fr       */
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
