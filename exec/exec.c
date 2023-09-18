/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:57:28 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/16 10:15:38 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_minishell *minishell)
{
	minishell->exec = exec_prep(minishell);
	here_doc_traverse(minishell);
	if (g_sig[4] == 1)
	{
		here_list_clear(minishell->here_doc);
		node_list_clear(minishell->node);
		exec_list_clear(minishell->exec);
		return ;
	}
	piping(minishell);
	node_list_clear(minishell->node);
	exec_list_clear(minishell->exec);
}
