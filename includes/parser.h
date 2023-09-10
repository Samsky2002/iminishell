/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:14:49 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/09 12:44:11 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/*typedef enum
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
} t_token_type;*/

/*typedef enum
{
	IN,
	OUT,
	APPEND,
	HERE_DOC
} t_redirect_type;*/

typedef struct	s_arg
{
	char			*arg;
	struct s_arg	*next;
} t_arg;

typedef struct	s_redirect
{
	char				*path;
	t_token_type		type;
	struct s_redirect	*next;
} t_redirect;

typedef struct	s_node
{
	t_arg			*args;
	t_redirect		*redirect;
	struct s_node	*next;
} t_node;

t_node	*parse(t_token *token);

//arg
t_arg	*new_arg(char *arg);
void	add_arg(t_arg **list, t_arg *new);
void	arg_list_clear(t_arg *arg);

//node
t_node	*new_list(t_arg *args, t_redirect *redirect);
void	add_list(t_node **list, t_node *new);
void	node_list_clear(t_node *node);

//redirect
t_redirect	*new_redirect(char *path, t_token_type type);
void		add_redirect(t_redirect **redirect, t_redirect *new);
void	redirect_list_clear(t_redirect *redirect);

# endif
