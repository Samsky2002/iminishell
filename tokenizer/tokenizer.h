/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:53:52 by oakerkao          #+#    #+#             */
/*   Updated: 2023/05/13 13:21:31 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER
#define TOKENIZER

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>

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

typedef enum
{
	T_GET,
	T_CHECK,
	T_UPDATE,
} t_get_type;

typedef enum
{
	GET,
	CHECK
} t_tokening_type;

typedef struct s_token
{
	t_token_type	type;
	char			*token;
	struct s_token	*next;
} t_token;

t_token	*tokenizer(char *line);

/* token_utils */
t_token	*new_token(char *token, t_token_type type);
void	add_token(t_token **list, t_token *new);

/* tokening*/
t_token	*tokening(t_token **head, t_tokening_type type);

/* get_token */
t_token	*get_token(t_get_type type);

#endif
