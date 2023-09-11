/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:53:52 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/11 17:37:22 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "minishell.h"

typedef enum s_token_type
{
	T_WORD,
	T_PIPE,
	T_HERE_DOC,
	T_IN,
	T_OUT,
	T_APPEND,
}	t_token_type;

typedef struct s_minishell	t_minishell;

typedef struct s_token
{
	t_token_type	type;
	char			*token;
	struct s_token	*next;
}	t_token;

t_token	*tokenizer(char *line, t_minishell *minishell);
t_token	*new_token(char *token, t_token_type type);
void	add_token(t_token **list, t_token *new);
void	token_list_clear(t_token *token);

#endif
