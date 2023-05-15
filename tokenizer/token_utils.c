/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:52:39 by oakerkao          #+#    #+#             */
/*   Updated: 2023/05/13 11:01:34 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token	*new_token(char *token, t_token_type type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	new_token->token = token;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_token **list, t_token *new)
{
	t_token	*head;

	head = *list;
	if (!head)
	{
		*list = new;
		return ;
	}
	while (head->next)
		head = head->next;
	head->next = new;
}
