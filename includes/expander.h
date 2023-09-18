/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 10:55:57 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/14 15:08:47 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

char	*get_var_name(char *str);
int		has_space(char *str, int type);
int		put_twod_size(t_list *lst);
char	**put_twod_array(t_list **lst);
void	expander_init(t_list **lst, char *quotes, int *i, t_list **tmp);
int		left_space_expand_variable(t_list **tmp, char **splited);
void	add_split(t_list **lst, t_list **tmp, char **splited);
void	expand_variable_helper(t_env *node, t_list **lst, t_list **tmp);
void	go_next(t_list **lst, t_list **tmp);
void	expand_exit_status(t_list **tmp, t_minishell *minishell);
int		expand_variable(t_list **lst, t_list **tmp, \
		char *str, t_minishell *minishell);
int		expand_quoted_variable(t_list **tmp, char *str, t_minishell *minishell);

#endif
