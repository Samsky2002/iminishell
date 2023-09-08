/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:57:54 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/08 12:42:03 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void function(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		//rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int main(int argc, char *argv[], char *enviro[])
{
	char	*red;
	t_token	*token;
	char	**list;

	get_env_list(enviro);
	signal(SIGQUIT, SIG_IGN);
	//error_printer();
	while (1)
	{
		signal(SIGINT, function);
		g_minishell.mini_error = SUCCESS;
		red = readline("minishell$ ");
		if (!red)
			exit(g_minishell.exit_s);
		if (!*red)
			continue ;
		tokenizer(red);
		syntax_error();
		if (g_minishell.mini_error == SUCCESS)
		{
			parse();
			token_list_clear(g_minishell.token);
			exec();
			node_list_clear(g_minishell.node);
			exec_list_clear(g_minishell.exec);
		}
		else
		{
			token_list_clear(g_minishell.token);
			exec_error();
			exec_error_msg();
		}
		add_history(red);
		free(red);
	}
	env_list_clear(g_minishell.list);
	exit(g_minishell.exit_s);
}
