/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:57:51 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/03 16:08:10 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef EXEC_H 
# define EXEC_H

typedef struct	s_exec_redirect
{
	t_token_type			type;
	char					**list;
	struct s_exec_redirect	*next;
} t_exec_redirect;

typedef struct	s_exec
{
	char			**args;
	t_exec_redirect	*redirect;
	struct s_exec	*next;
} t_exec;

typedef struct	s_context
{
	int	fd[2];
} t_context;

void	exec();

/* exec_utils */
t_exec	*new_exec(char **arr, t_exec_redirect *redirect);
void	add_exec(t_exec **exec, t_exec *new);
void	print_exec();

/* exec_redirect */
t_exec_redirect	*new_exec_redirect(char **arr, t_token_type type);
void	add_exec_redirect(t_exec_redirect **redirect, t_exec_redirect *new);

/* redirect */
void	redirect(t_exec_redirect *redirect);
void	out(char **path);
void	in(char **path);
void	append(char **path);

/* exec_child */
void	exec_child(t_context *ctx);

# endif
