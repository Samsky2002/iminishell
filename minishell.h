/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 07:49:04 by oakerkao          #+#    #+#             */
/*   Updated: 2023/05/13 11:53:00 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include "env.h"
# include "builtin.h"
# include "tokenizer.h"
# include "parser.h"
# include <readline/readline.h>
# include <readline/history.h>


typedef struct s_env	t_env;
typedef struct s_token t_token;
typedef struct	s_manager
{
	t_env		*list;
	t_token		*token;
}				t_manager;

 t_manager	g_manager;

char	**expander(char *str);

# endif
