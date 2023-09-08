/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:54:59 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/08 10:53:38 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error_msg(void)
{
	if (g_minishell.mini_error == 1)
		ft_putstr_fd("minishell: syntax error\n", 2);
}

void	var_init(t_syntax_type *type, t_syntax_type *current)
{
	*type = -1;
	*current = -1;
}

void	syntax_error(void)
{
	t_token			*token;
	t_syntax_type	type;
	t_syntax_type	current;

	var_init(&type, &current);
	token = g_minishell.token;
	if (token->type == T_PIPE)
		g_minishell.mini_error = SYNTAX_ERROR;
	while (token && g_minishell.mini_error == SUCCESS)
	{
		if ((token->next == NULL && token->type != T_WORD))
			g_minishell.mini_error = SYNTAX_ERROR;
		if (token->type == T_PIPE)
			type = S_PIPE;
		else if (token->type == T_WORD)
			type = S_WORD;
		else
			type = S_REDIRECT;
		if ((current == S_REDIRECT && type != S_WORD) \
				|| (current == S_PIPE && type == S_PIPE))
			g_minishell.mini_error = SYNTAX_ERROR;
		current = type;
		token = token->next;
	}
}

void	exec_error(void)
{
	if (g_minishell.mini_error == CMD_NOT_FOUND \
			|| g_minishell.mini_error == NO_SUCH_PROGRAM)
		g_minishell.exit_s = 127;
	else if (g_minishell.mini_error == PERMISSION_DENIED_PROG)
		g_minishell.exit_s = 126;
	else if (g_minishell.mini_error == NO_SUCH_FILE ||
			g_minishell.mini_error == PERMISSION_DENIED_FILE)
		g_minishell.exit_s = 1;
	else if (g_minishell.mini_error == SYNTAX_ERROR)
		g_minishell.exit_s = 258;
}

void	exec_error_msg(void)
{
	if (g_minishell.mini_error == CMD_NOT_FOUND)
		ft_putstr_fd("minishell: command not found\n", 2);
	else if (g_minishell.mini_error == NO_SUCH_FILE \
			|| g_minishell.mini_error == NO_SUCH_PROGRAM)
		ft_putstr_fd("minishell: No such file or directory\n", 2);
	else if (g_minishell.mini_error == PERMISSION_DENIED_PROG \
			|| g_minishell.mini_error == PERMISSION_DENIED_FILE)
		ft_putstr_fd("minishell: Permission denied\n", 2);
	else if (g_minishell.mini_error == SYNTAX_ERROR)
		ft_putstr_fd("minishell: syntax error\n", 2);
}

void	error_printer(void)
{
	if (g_minishell.mini_error == CMD_NOT_FOUND)
		ft_putstr_fd("CMD_NOT_FOUND\n", 2);
	if (g_minishell.mini_error == SYNTAX_ERROR)
		ft_putstr_fd("SYNTAX_ERROR\n", 2);
	if (g_minishell.mini_error == NO_SUCH_PROGRAM)
		ft_putstr_fd("NO_SUCH_PROGRAM\n", 2);
	if (g_minishell.mini_error == PERMISSION_DENIED_PROG)
		ft_putstr_fd("PERMISSION_DENIED_PROG\n", 2);
	if (g_minishell.mini_error == NO_SUCH_FILE)
		ft_putstr_fd("NO_SUCH_FILE\n", 2);
	if (g_minishell.mini_error == PERMISSION_DENIED_FILE)
		ft_putstr_fd("PERMISSION_DENIED_FILE\n", 2);
	if (g_minishell.mini_error == SUCCESS)
		ft_putstr_fd("SUCCESS\n", 2);
}
