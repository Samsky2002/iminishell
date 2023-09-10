/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:14:26 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/10 17:12:51 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_var(t_arg **args, t_redirect **redirect)
{
	*args = NULL;
	*redirect = NULL;
}

void	parse_arg_redirect(t_arg **args, t_redirect **redirect, t_token *token)
{
	t_token_type	type;

	if (token->type == T_WORD)
		add_arg(args, new_arg(token->token));
	else
	{
		type = token->type;
		token = token->next;
		add_redirect(redirect, new_redirect(token->token, type));
	}
}

t_node	*parse(t_token *token)
{
	t_node			*node;
	t_arg			*args;
	t_redirect		*redirect;

	node = NULL;
	while (token)
	{
		args = NULL;
		redirect = NULL;
		while (token && token->type != T_PIPE)
		{
			parse_arg_redirect(&args, &redirect, token);
			token = token->next;
		}
		add_list(&node, new_list(args, redirect));
		if (token)
			token = token->next;
	}
	return (node);
}
