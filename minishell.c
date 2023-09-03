/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:57:54 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/03 09:59:30 by oakerkao         ###   ########.fr       */
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
		free_token_list();
		free(red);
		syntax_error();
		if (!g_minishell.s_error)
		{
			parse();
			print_list();
			//expanded();
			//exec();
			node_list_clear(g_minishell.node);
		}
		token_list_clear(g_minishell.token);
		add_history(red);
	}
	env_list_clear(g_minishell.list);
}
