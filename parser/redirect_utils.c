/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:19:45 by oakerkao          #+#    #+#             */
/*   Updated: 2023/06/14 17:34:20 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_redirect	*new_redirect(char *path, t_token_type type)
{
	t_redirect	*new;

	new = malloc(sizeof(t_redirect));
	new->path = path;
	new->type= type;
	new->next = NULL;
	return (new);
}

void	add_redirect(t_redirect **redirect, t_redirect *new)
{
	t_redirect	*head;

	if (!*redirect)
	{
		*redirect = new;
		return ;	
	}
	head = *redirect;
	while (head->next)
		head = head->next;
	head->next = new;
}
