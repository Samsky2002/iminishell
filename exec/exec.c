/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:57:28 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/03 16:11:11 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**node_args(t_node *node)
{
	char	**expanded;
	char	**arr_arg;
	t_list	*lst;

	lst = NULL;
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
	return (arr_arg);
}

t_exec_redirect	*node_redirect(t_node *node)
{
	char			**arr_red;
	char			**expanded;
	t_list			*lst;
	t_exec_redirect	*redirect;

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
		add_exec_redirect(&redirect, \
				new_exec_redirect(arr_red, node->redirect->type));
		node->redirect = node->redirect->next;
	}
	return (redirect);
}

void	exec_prep(void)
{
	t_node			*node;
	t_exec			*exec;
	t_exec_redirect	*redirect;
	char			**arr_arg;

	node = g_minishell.node;
	redirect = NULL;
	exec = NULL;
	while (node)
	{
		arr_arg = node_args(node);
		redirect = node_redirect(node);
		add_exec(&exec, new_exec(arr_arg, redirect));
		node = node->next;
	}
	g_minishell.exec = exec;
}

void	exec(void)
{
	t_context	ctx;
	/*ctx.fd[0] = 0;
	ctx.fd[1] = 1;*/
	exec_prep();
	print_exec();
	//exec_child(&ctx);
}
