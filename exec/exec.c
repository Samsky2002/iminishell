/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:57:28 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/10 20:15:49 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_minishell *minishell)
{
	minishell->exec = exec_prep(minishell);
	here_doc_traverse(minishell);
	piping(minishell);
	//print_exec(minishell->exec);
	node_list_clear(minishell->node);
	exec_list_clear(minishell->exec);
}
