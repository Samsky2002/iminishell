/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:54:59 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/10 16:53:13 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	var_init(t_syntax_type *type, t_syntax_type *current)
{
	*type = -1;
	*current = -1;
}

void	syntax_error(t_minishell *minishell)
{
	t_token			*token;
	t_syntax_type	type;
	t_syntax_type	current;

	token = minishell->token;
	var_init(&type, &current);
	if (token->type == T_PIPE)
		minishell->mini_error = SYNTAX_ERROR;
	while (token && minishell->mini_error == SUCCESS)
	{
		if ((token->next == NULL && token->type != T_WORD))
			minishell->mini_error = SYNTAX_ERROR;
		if (token->type == T_PIPE)
			type = S_PIPE;
		else if (token->type == T_WORD)
			type = S_WORD;
		else
			type = S_REDIRECT;
		if ((current == S_REDIRECT && type != S_WORD) \
				|| (current == S_PIPE && type == S_PIPE))
			minishell->mini_error = SYNTAX_ERROR;
		current = type;
		token = token->next;
	}
}

void	exec_error(t_minishell *minishell)
{
	if (minishell->mini_error == CMD_NOT_FOUND \
			|| minishell->mini_error == NO_SUCH_PROGRAM)
		minishell->exit_s = 127;
	else if (minishell->mini_error == PERMISSION_DENIED_PROG)
		minishell->exit_s = 126;
	else if (minishell->mini_error == NO_SUCH_FILE || \
			minishell->mini_error == PERMISSION_DENIED_FILE || \
			minishell->mini_error == AMBIGUOUS || \
			minishell->mini_error == NOT_VALID || \
			minishell->mini_error == TOO_MANY_ARGS)
		minishell->exit_s = 1;
	else if (minishell->mini_error == SYNTAX_ERROR)
		minishell->exit_s = 258;
	else if (minishell->mini_error == NUMERIC_ARG_REQ)
		minishell->exit_s = 255;
	else if (minishell->mini_error == SUCCESS)
		minishell->exit_s = 0;
}

void	exec_error_msg(t_minishell *minishell)
{
	if (minishell->mini_error == CMD_NOT_FOUND)
		ft_putstr_fd("minishell: command not found\n", 2);
	else if (minishell->mini_error == NO_SUCH_FILE \
			|| minishell->mini_error == NO_SUCH_PROGRAM)
		ft_putstr_fd("minishell: No such file or directory\n", 2);
	else if (minishell->mini_error == PERMISSION_DENIED_PROG \
			|| minishell->mini_error == PERMISSION_DENIED_FILE)
		ft_putstr_fd("minishell: foo: Permission denied\n", 2);
	else if (minishell->mini_error == SYNTAX_ERROR)
		ft_putstr_fd("minishell: syntax error\n", 2);
	else if (minishell->mini_error == AMBIGUOUS)
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
	else if (minishell->mini_error == NUMERIC_ARG_REQ)
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
	else if (minishell->mini_error == TOO_MANY_ARGS)
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	else if (minishell->mini_error == NOT_VALID)
		ft_putstr_fd("minishell: export: not a valid identifier\n", 2);
}

void	error_printer(t_minishell *minishell)
{
	if (minishell->mini_error == CMD_NOT_FOUND)
		ft_putstr_fd("CMD_NOT_FOUND\n", 2);
	if (minishell->mini_error == SYNTAX_ERROR)
		ft_putstr_fd("SYNTAX_ERROR\n", 2);
	if (minishell->mini_error == NO_SUCH_PROGRAM)
		ft_putstr_fd("NO_SUCH_PROGRAM\n", 2);
	if (minishell->mini_error == PERMISSION_DENIED_PROG)
		ft_putstr_fd("PERMISSION_DENIED_PROG\n", 2);
	if (minishell->mini_error == NO_SUCH_FILE)
		ft_putstr_fd("NO_SUCH_FILE\n", 2);
	if (minishell->mini_error == PERMISSION_DENIED_FILE)
		ft_putstr_fd("PERMISSION_DENIED_FILE\n", 2);
	if (minishell->mini_error == SUCCESS)
		ft_putstr_fd("SUCCESS\n", 2);
}
