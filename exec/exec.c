/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:57:28 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/01 16:48:55 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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

void	exec_prep()
{
	t_node	*node;
	t_exec	*exec;
	t_list	*lst;
	t_exec_redirect	*redirect;
	char	**arr_arg;
	char	**arr_red;
	char	**expanded;

	node = g_minishell.node;
	lst = NULL;
	redirect = NULL;
	exec = NULL;
	while (node)
	{
		while (node->args)
		{
			expanded = expander(node->args->arg);
			while (*expanded)
			{
				ft_lstadd_back(&lst, ft_lstnew(*expanded));
				expanded++;	
			}
			node->args = node->args->next;
		}
		arr_arg = put_twod_array(&lst);
		redirect = NULL;
		while (node->redirect)
		{
			lst = NULL;
			expanded = expander(node->redirect->path);
			while (*expanded)
			{
				ft_lstadd_back(&lst, ft_lstnew(*expanded));
				expanded++;	
			}
			arr_red = put_twod_array(&lst);
			add_exec_redirect(&redirect, new_exec_redirect(arr_red, node->redirect->type));
			node->redirect = node->redirect->next;
		}
		add_exec(&exec, new_exec(arr_arg, redirect));
		node = node->next;
	}
	g_minishell.exec = exec;
}

void	exec()
{
	t_context	ctx;
	/*ctx.fd[0] = 0;
	ctx.fd[1] = 1;*/
	//exec_prep();
	print_exec();
	//exec_child(&ctx);
}
