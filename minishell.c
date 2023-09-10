/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:57:54 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/10 17:16:08 by oakerkao         ###   ########.fr       */
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
	char		*red;
	t_minishell	minishell;

	minishell.enviro = enviro;
	minishell.exit_s = 0;
	minishell.mini_error = SUCCESS;
	minishell.env = get_env_list(enviro);
	signal(SIGQUIT, SIG_IGN);
	//error_printer();
	while (1)
	{
		signal(SIGINT, function);
		minishell.mini_error = SUCCESS;
		red = readline("minishell$ ");
		if (!red)
			break ;
		if (!*red)
			continue ;
		minishell.token = tokenizer(red, &minishell);
		syntax_error(&minishell);
		if (minishell.mini_error == SUCCESS)
		{
			minishell.node = parse(minishell.token);
			token_list_clear(minishell.token);
			exec(&minishell);
		}
		else
		{
			token_list_clear(minishell.token);
			exec_error(&minishell);
			exec_error_msg(&minishell);
		}
		add_history(red);
		free(red);
	}
	env_list_clear(minishell.env);
	exit(minishell.exit_s);
}
