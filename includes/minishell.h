/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 07:49:04 by oakerkao          #+#    #+#             */
/*   Updated: 2023/06/14 16:15:10 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "env.h"
# include "builtin.h"
# include "tokenizer.h"
# include "parser.h"


typedef struct s_env	t_env;
typedef struct s_token	t_token;
typedef struct s_node	t_node;

void	find_type(int i);

typedef struct	s_minishell
{
	t_env		*list;
	t_token		*token;
	t_node		*node;
}				t_minishell;

 t_minishell	g_minishell;

char	**expander(char *str);

# endif
