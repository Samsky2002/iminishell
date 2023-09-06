/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:54:52 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/04 10:56:37 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**node_args(t_node *node)
{
	char	**expanded;
	char	**arr_arg;
	t_list	*lst;
	int		i;
	t_arg	*tmp;

	lst = NULL;
	tmp = node->args;
	while (node->args)
	{
		i = 0;
		expanded = expander(node->args->arg);
		while (expanded[i])
		{
			ft_lstadd_back(&lst, ft_lstnew(expanded[i]));
			i++;
		}
		free(expanded);
		node->args = node->args->next;
	}
	arr_arg = put_twod_array(&lst);
	ft_lstclear(&lst, free);
	node->args = tmp;
	return (arr_arg);
}

t_exec_redirect	*node_redirect(t_node *node, int i)
{
	char			**arr_red;
	char			**expanded;
	t_list			*lst;
	t_exec_redirect	*redirect;
	t_redirect		*tmp;

	redirect = NULL;
	tmp = node->redirect;
	while (node->redirect)
	{
		lst = NULL;
		i = -1;
		expanded = expander(node->redirect->path);
		while (expanded[++i])
			ft_lstadd_back(&lst, ft_lstnew(expanded[i]));
		free(expanded);
		arr_red = put_twod_array(&lst);
		ft_lstclear(&lst, free);
		add_exec_redirect(&redirect, \
				new_exec_redirect(arr_red, node->redirect->type));
		node->redirect = node->redirect->next;
	}
	node->redirect = tmp;
	return (redirect);
}

void	exec_prep(void)
{
	t_node			*node;
	t_exec			*exec;
	t_exec_redirect	*redirect;
	char			**arr_arg;
	int				i;

	node = g_minishell.node;
	redirect = NULL;
	exec = NULL;
	while (node)
	{
		arr_arg = node_args(node);
		redirect = node_redirect(node, i);
		add_exec(&exec, new_exec(arr_arg, redirect));
		node = node->next;
	}
	g_minishell.exec = exec;
}
