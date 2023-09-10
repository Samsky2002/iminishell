/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:00:21 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/09 17:34:30 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef BUILTIN_H
# define BUILTIN_H

# include <string.h>
# include "minishell.h"

typedef struct s_minishell	t_minishell;

void	unset(char **args, t_minishell *minishell);
void	echo(char **cmd);
void	export(char **argv, t_minishell *minishell);
void	env(t_minishell *minishell);
void	pwd(void);
void	cd(char *path, t_minishell *minishell);
void	ft_exit(char **args, t_minishell *minishell);

/* utils */
int		check_key(char *str);
void	remove_node(char *key, t_minishell *minishell);

# endif
