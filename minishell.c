/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:57:54 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/18 10:18:05 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	function(int sig)
{
	if (sig == SIGINT)
	{
		if (g_sig[0] == 0 && g_sig[2] == 0)
		{
			printf("\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else if (g_sig[0] == 1 && g_sig[2] == 0)
			g_sig[1] = 130;
		if (g_sig[2] == 1)
		{
			g_sig[4] = 1;
			close(g_sig[3]);
		}
	}
	else if (sig == SIGQUIT)
		g_sig[1] = 131;
}

void	main_init(t_minishell *minishell, char **enviro)
{
	minishell->enviro = enviro;
	minishell->exit_s = 0;
	minishell->mini_error = SUCCESS;
	minishell->env = get_env_list(enviro);
	signal(SIGQUIT, function);
}

void	main_help(t_minishell *minishell)
{
	if (minishell->mini_error == SUCCESS)
	{
		minishell->node = parse(minishell->token);
		token_list_clear(minishell->token);
		exec(minishell);
	}
	else
	{
		token_list_clear(minishell->token);
		exec_error(minishell);
		exec_error_msg(minishell);
	}
}

void	init_sig(void)
{
	signal(SIGINT, function);
	g_sig[1] = 0;
	g_sig[2] = 0;
	g_sig[4] = 0;
}

int	main(int argc, char *argv[], char *enviro[])
{
	char		*red;
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	main_init(&minishell, enviro);
	while (1)
	{
		init_sig();
		minishell.mini_error = SUCCESS;
		g_sig[0] = 0;
		red = readline("minishell$ ");
		g_sig[0] = 1;
		if (!red)
			break ;
		minishell.token = tokenizer(red, &minishell);
		syntax_error(&minishell);
		main_help(&minishell);
		add_history(red);
		free(red);
	}
	env_list_clear(minishell.env);
	exit(minishell.exit_s);
}
