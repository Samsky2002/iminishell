/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:14:26 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/02 17:39:17 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_var(t_arg **args, t_redirect **redirect)
{
	*args = NULL;
	*redirect = NULL;
}

void	parse(void)
{
	t_token			*token;
	t_arg			*args;
	t_redirect		*redirect;
	t_token_type	type;

	token = g_minishell.token;
	while (token)
	{
		init_var(&args, &redirect);
		while (token && token->type != T_PIPE)
		{
			if (token->type == T_WORD)
				add_arg(&args, new_arg(token->token));
			else
			{
				type = token->type;
				token = token->next;
				add_redirect(&redirect, new_redirect(token->token, type));
			}
			token = token->next;
		}
		add_list(&g_minishell.node, new_list(args, redirect));
		if (token)
			token = token->next;
	}
}
