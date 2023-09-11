/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:57:28 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/11 18:00:50 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_minishell *minishell)
{
	minishell->exec = exec_prep(minishell);
	here_doc_traverse(minishell);
	piping(minishell);
	node_list_clear(minishell->node);
	exec_list_clear(minishell->exec);
}
