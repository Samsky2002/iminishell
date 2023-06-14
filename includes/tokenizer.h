/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:53:52 by oakerkao          #+#    #+#             */
/*   Updated: 2023/06/14 17:35:11 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "minishell.h"

typedef enum
{
	T_WORD,
	T_PIPE,
	T_HERE_DOC,
	T_IN,
	T_OUT,
	T_APPEND,
	T_NULL,
	T_AND,
	T_OR,
	T_OPEN_PAR,
	T_CLOSE_PAR,
} t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*token;
	struct s_token	*next;
} t_token;

void	tokenizer(char *line);

/* token_utils */
t_token	*new_token(char *token, t_token_type type);
void	add_token(t_token **list, t_token *new);


#endif
