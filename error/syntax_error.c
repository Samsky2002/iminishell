/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:54:59 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/04 10:15:34 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error_msg(void)
{
	if (g_minishell.s_error == 1)
		printf("minishell: syntax error\n");
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
		g_minishell.s_error = 1;
	while (token && g_minishell.s_error == 0)
	{
		if ((token->next == NULL && token->type != T_WORD))
			g_minishell.s_error = 1;
		if (token->type == T_PIPE)
			type = S_PIPE;
		else if (token->type == T_WORD)
			type = S_WORD;
		else
			type = S_REDIRECT;
		if ((current == S_REDIRECT && type != S_WORD) \
				|| (current == S_PIPE && type == S_PIPE))
			g_minishell.s_error = 1;
		current = type;
		token = token->next;
	}
	syntax_error_msg();
}
