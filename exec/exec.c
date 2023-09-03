/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:57:28 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/03 19:11:34 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**node_args(t_node *node)
{
	char	**expanded;
	char	**arr_arg;
	t_list	*lst;
	int		i;
	t_arg	*tmp_args;

	i = 0;
	lst = NULL;
	tmp_args = node->args;
	while (node->args)
	{
		expanded = expander(node->args->arg);
		i = 0;
		while (expanded[i])
		{
			ft_lstadd_back(&lst, ft_lstnew(expanded[i]));
			i++;
		}
		node->args = node->args->next;
		free (expanded);
	}
	node->args = tmp_args;
	arr_arg = put_twod_array(&lst);
	ft_lstclear(&lst, free);
	return (arr_arg);
}

t_exec_redirect	*node_redirect(t_node *node)
{
	char			**arr_red;
	char			**expanded;
	t_list			*lst;
	t_exec_redirect	*redirect;
	int				i;

	redirect = NULL;
	while (node->redirect)
	{
		lst = NULL;
		expanded = expander(node->redirect->path);
		i = 0;
		while (expanded[i])
		{
			ft_lstadd_back(&lst, ft_lstnew(expanded[i]));
			i++;
		}
		free (expanded);
		arr_red = put_twod_array(&lst);
		ft_lstclear(&lst, free);
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
	exec_prep();
	exec_list_clear(g_minishell.exec);
}

// free expanded
// make exec_clear function
