/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 10:55:57 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/06 18:07:53 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef EXPANDER_H
# define EXPANDER_H

void	expanded(void);
char	*get_var_name(char *str);
int		has_space(char *str, int type);
int		put_twod_size(t_list *lst);
char	**put_twod_array(t_list **lst);
void	expander_init(t_list **lst, char *quotes, int *i, t_list **tmp);
int		left_space_expand_variable(t_list **tmp, char **splited);
void	add_split(t_list **lst, t_list **tmp, char **splited);
void	expand_variable_helper(t_env *node, t_list **lst, t_list **tmp);

# endif
