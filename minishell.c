/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:57:54 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/04 16:01:58 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *enviro[])
{
	char	*red;
	t_token	*token;
	char	**list;

	get_env_list(enviro);
	while (1)
	{
		red = readline("> ");
		if (!red)
			break ;
		if (!*red)
			continue ;
		tokenizer(red);
		syntax_error();
		if (!g_minishell.s_error)
		{
			parse();
			token_list_clear(g_minishell.token);
			//print_list();
			exec();
			node_list_clear(g_minishell.node);
			exec_list_clear(g_minishell.exec);
		}
		else
			token_list_clear(g_minishell.token);
		add_history(red);
		free(red);
	}
	env_list_clear(g_minishell.list);
}
