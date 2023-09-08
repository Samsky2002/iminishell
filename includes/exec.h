/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:57:51 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/08 10:26:28 by oakerkao         ###   ########.fr       */
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

typedef struct s_fd
{
	int			fd;
	struct s_fd	*next;
} t_fd;

void	exec();

/* exec_utils */
t_exec	*new_exec(char **arr, t_exec_redirect *redirect);
void	add_exec(t_exec **exec, t_exec *new);
void	print_exec();
void	exec_redirect_list_clear(t_exec_redirect *redirect);
void	exec_list_clear(t_exec *exec);
int		exec_list_count(t_exec *exec);

/* exec_redirect */
t_exec_redirect	*new_exec_redirect(char **arr, t_token_type type);
void	add_exec_redirect(t_exec_redirect **redirect, t_exec_redirect *new);

/* redirect */
void	redirect(t_exec_redirect *redirect);
void	out(char **path);
void	in(char **path);
void	append(char **path);

/* exec_child */
void	exec_child(t_exec *exec);
char	*path_getter(char *cmd);

/* exec_prep */
void	exec_prep(void);

/* piping */
void	piping(void);

/* builtins */
void	child_builtins(char **arr);
int		child_builtins_check(char **arr);
void	parent_builtins(char **arr);
int		parent_builtins_check(char **arr);

/* here_doc */
void	here_doc_traverse();
void	here_doc(t_fd **list, char *delimiter);
void	add_here_list(t_fd **list, t_fd *new);
t_fd	*new_here_list(int fd);
void	got_here_doc(t_exec_redirect *redirect);
void	here_list_clear(t_fd *list);

# endif
