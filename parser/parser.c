/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:14:26 by oakerkao          #+#    #+#             */
/*   Updated: 2023/06/14 18:26:53 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	parse(void)
{
	t_token	*token;
	t_node	*node;
	t_arg	*args;
	t_redirect	*redirect;
	t_token_type	type;

	node = NULL;
	args = NULL;
	redirect = NULL;
	token = g_minishell.token;
	while (token)
	{
		while (token && token->type != T_PIPE)
		{
			if (token->type == T_WORD)
				add_arg(&args, new_arg(token->token));
			else if (token->type == T_IN | token->type == T_OUT || token->type == T_HERE_DOC || token->type == T_APPEND)
			{
				type = token->type;
				if (token->next)
					token = token->next;
				add_redirect(&redirect, new_redirect(token->token, type));
			}
			token = token->next;
		}
		add_list(&node, new_list(args, redirect));
		args = NULL;
		redirect= NULL;
		if (token)
			token = token->next;
	}
	g_minishell.node = node;
}
