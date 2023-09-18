/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 07:49:04 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/14 12:48:15 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include "../libft/libft.h"
# include "env.h"
# include "builtin.h"
# include "tokenizer.h"
# include "parser.h"
# include "exec.h"
# include "mini_errors.h"
# include "expander.h"

typedef struct s_env	t_env;
typedef struct s_token	t_token;
typedef struct s_node	t_node;
int						g_sig[5];

typedef struct s_minishell
{
	char			**enviro;
	t_env			*env;
	t_token			*token;
	t_node			*node;
	t_exec			*exec;
	t_fd			*here_doc;
	t_exec_error	mini_error;
	int				exit_s;
}	t_minishell;

void	expander(t_list **lst, char *str, t_minishell *minishell);
void	find_type(int i);
char	*char_join(char *str, char c);
char	**put_twod_array(t_list **lst);
void	print_tokens(t_token *token);
void	print_list(t_node *node);
void	free_twod_array(char **arr);
void	rl_replace_line(const char *text, int clear_undo);
void	function(int sig);

// to delete
void	print_exec(t_exec *exec);
void	print_list(t_node *node);

#endif
