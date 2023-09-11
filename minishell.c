/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:57:54 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/11 20:56:22 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	function(int sig)
{
	if (sig == SIGINT)
	{
		if (globe[0] == 0)
		{
			printf("\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else
		{
			globe[1] = 130;
		}
	}
	else if (sig == SIGQUIT)
	{
		if (globe[0] == 1)
		{
			printf(" Quit: 3\n");
			globe[1] = 131;
		}
		return ;
	}
}

void	main_init(t_minishell *minishell, char **enviro)
{
	minishell->enviro = enviro;
	minishell->exit_s = 0;
	minishell->mini_error = SUCCESS;
	minishell->env = get_env_list(enviro);
	signal(SIGQUIT, function);
	signal(SIGINT, function);
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

int	main(int argc, char *argv[], char *enviro[])
{
	char		*red;
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	main_init(&minishell, enviro);
	while (1)
	{
		globe[1] = 0;
		minishell.mini_error = SUCCESS;
		globe[0] = 0;
		red = readline("minishell$ ");
		globe[0] = 1;
		if (!red)
			break ;
		if (!*red)
			continue ;
		minishell.token = tokenizer(red, &minishell);
		syntax_error(&minishell);
		main_help(&minishell);
		add_history(red);
		free(red);
	}
	env_list_clear(minishell.env);
	exit(minishell.exit_s);
}
