/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:52:39 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/14 11:53:10 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (!*list)
	{
		*list = new;
		return ;
	}
	head = *list;
	while (head->next)
		head = head->next;
	head->next = new;
}

void	token_list_clear(t_token *token)
{
	t_token	*head;

	if (!token)
		return ;
	head = token;
	while (head)
	{
		head = token->next;
		free(token->token);
		free(token);
		token = head;
	}
}
