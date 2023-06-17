/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:54:59 by oakerkao          #+#    #+#             */
/*   Updated: 2023/06/16 16:24:18 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	syntax_error_msg()
{
	if (g_minishell.s_error == 1)
		printf("minishell: syntax error\n");
}

// 0 redirections
// 1 pipe
// 2 word

// t -> type
// c -> current_type
void	syntax_error()
{
	t_token	*token;
	int	type;
	int	current;

	type = -1;
	current = -1;
	token = g_minishell.token;
	while (token && g_minishell.s_error == 0)
	{
		if (token->next == NULL && token->type != T_WORD)
				g_minishell.s_error = 1;
		if (token->type != T_PIPE && token->type != T_WORD)
			type = 0;
		else if (token->type == T_PIPE)
			type = 1;
		else if (token->type == T_WORD)
			type = 2;
		if ((current == 0 && type != 2) || (current == 1 && type == 1))
			g_minishell.s_error = 1;
		current = type;
		token = token->next;
	}
	syntax_error_msg();
}
