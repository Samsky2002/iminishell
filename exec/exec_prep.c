/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:54:52 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/14 16:25:37 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**node_args(t_node *node, t_minishell *minishell)
{
	char	**arr_arg;
	t_list	*lst;
	t_arg	*tmp;

	lst = NULL;
	tmp = node->args;
	while (node->args)
	{
		expander(&lst, node->args->arg, minishell);
		node->args = node->args->next;
	}
	arr_arg = put_twod_array(&lst);
	ft_lstclear(&lst, free);
	node->args = tmp;
	return (arr_arg);
}

char	**single_to_double(char *str)
{
	char	**arr;

	arr = malloc(2 * sizeof(char *));
	arr[0] = ft_strdup(str);
	arr[1] = NULL;
	return (arr);
}

char	**not_here_doc(t_minishell *minishell, t_list **lst, t_node *node)
{
	int		i;
	char	**arr_red;	

	i = 0;
	arr_red = NULL;
	expander(lst, node->redirect->path, minishell);
	arr_red = put_twod_array(lst);
	ft_lstclear(lst, free);
	return (arr_red);
}

t_exec_redirect	*node_redirect(t_node *node, t_minishell *minishell)
{
	char			**arr_red;
	t_list			*lst;
	t_exec_redirect	*redirect;
	t_redirect		*tmp;

	redirect = NULL;
	tmp = node->redirect;
	while (node->redirect)
	{
		lst = NULL;
		if (node->redirect->type != T_HERE_DOC)
			arr_red = not_here_doc(minishell, &lst, node);
		else
			arr_red = single_to_double(node->redirect->path);
		add_exec_redirect(&redirect, \
				new_exec_redirect(arr_red, node->redirect->type));
		node->redirect = node->redirect->next;
	}
	node->redirect = tmp;
	return (redirect);
}

t_exec	*exec_prep(t_minishell *minishell)
{
	t_exec			*exec;
	t_exec_redirect	*redirect;
	t_node			*node;
	char			**arr_arg;

	redirect = NULL;
	exec = NULL;
	node = minishell->node;
	while (node)
	{
		arr_arg = node_args(node, minishell);
		redirect = node_redirect(node, minishell);
		add_exec(&exec, new_exec(arr_arg, redirect));
		node = node->next;
	}
	return (exec);
}
