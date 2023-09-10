/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:54:52 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/10 10:33:52 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**node_args(t_node *node, t_minishell *minishell)
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
		expanded = expander(node->args->arg, minishell);
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

char	**single_to_double(char *str)
{
	char	**arr;

	arr = malloc(2 * sizeof(char *));	
	arr[0] = ft_strdup(str);
	arr[1] = NULL;
	return (arr);
}

t_exec_redirect	*node_redirect(t_node *node, int i, t_minishell *minishell)
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
		if (node->redirect->type != T_HERE_DOC)
		{
			expanded = expander(node->redirect->path, minishell);
			while (expanded[++i])
				ft_lstadd_back(&lst, ft_lstnew(expanded[i]));
			free(expanded);
			arr_red = put_twod_array(&lst);
			ft_lstclear(&lst, free);
		}
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
	int				i;

	redirect = NULL;
	exec = NULL;
	node = minishell->node;
	while (node)
	{
		arr_arg = node_args(node, minishell);
		redirect = node_redirect(node, i, minishell);
		add_exec(&exec, new_exec(arr_arg, redirect));
		node = node->next;
	}
	return (exec);
}
