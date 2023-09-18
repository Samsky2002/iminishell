/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:57:51 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/16 10:24:11 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H 
# define EXEC_H

typedef struct s_exec_redirect
{
	t_token_type			type;
	char					**list;
	struct s_exec_redirect	*next;
}	t_exec_redirect;

typedef struct s_exec
{
	char			**args;
	t_exec_redirect	*redirect;
	struct s_exec	*next;
}	t_exec;

typedef struct s_fd
{
	int			fd;
	struct s_fd	*next;
}	t_fd;

void			exec(t_minishell *minishell);
t_exec			*new_exec(char **arr, t_exec_redirect *redirect);
void			add_exec(t_exec **exec, t_exec *new);
void			exec_redirect_list_clear(t_exec_redirect *redirect);
void			exec_list_clear(t_exec *exec);
int				exec_list_count(t_exec *exec);
int				twod_array_size(char **arr);
t_exec_redirect	*new_exec_redirect(char **arr, t_token_type type);
void			add_exec_redirect(t_exec_redirect **redirect, \
		t_exec_redirect *new);
void			redirect(t_exec_redirect *redirect, t_minishell *minishell);
void			out(char **path, t_minishell *minishell);
void			in(char **path, t_minishell *minishell);
void			append(char **path, t_minishell *minishell);
void			exec_child(t_minishell *minishell, t_exec *exec);
char			*path_getter(char *cmd, t_minishell *minishell);
t_exec			*exec_prep(t_minishell *minishell);
void			piping(t_minishell *minishell);
void			child_builtins(char **arr, t_minishell *minishell);
int				child_builtins_check(char **arr);
void			parent_builtins(char **arr, t_minishell *minishell);
int				parent_builtins_check(char **arr);
void			here_doc_traverse(t_minishell *minishell);
void			here_doc(t_fd **list, char *delimiter, t_minishell *minishell);
void			add_here_list(t_fd **list, t_fd *new);
t_fd			*new_here_list(int fd);
void			got_here_doc(t_exec_redirect *redirect, t_minishell *minishell);
void			here_list_clear(t_fd *list);
void			exec_child_clear(t_minishell *minishell);
void			exec_child_helper(char **args, \
		t_minishell *minishell, char *path);
void			here_doc_expansion(t_list **lst, t_minishell *minishell, \
		char *str);

#endif
