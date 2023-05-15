/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:14:49 by oakerkao          #+#    #+#             */
/*   Updated: 2023/05/13 11:50:52 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum
{
	AST_PIPE,
	AST_COMMAND,
} t_type;

typedef enum
{
	SIMPLE_CMD,
	REDIRECT
} t_command_type;

typedef enum
{
	IN,
	OUT,
	APPEND,
	HERE_DOC
} t_redirect_type;

typedef struct s_ast
{
	t_type type;
	void	*data;
} t_ast;

typedef struct s_pipe
{
	t_ast *left_child;
	t_ast *right_child;
} t_pipe;

typedef struct s_simple_cmd
{
	char	**args;
} t_simple_cmd;

typedef struct s_redirect
{
	t_redirect_type	type;
	char	*file;
} t_redirect;

typedef struct s_redirection
{
	t_redirect				*redirect;
	struct s_redirection	*s_redirection;
} t_redirection;

typedef struct s_command
{
	t_simple_cmd	*cmd;
	t_redirection		*redirection;
} t_command;


t_ast	*parse(void);

# endif
