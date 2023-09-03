/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 10:55:57 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/03 14:52:47 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef EXPANDER_H
# define EXPANDER_H

void	expanded(void);
char	*get_var_name(char *str);
int		has_space(char *str, int type);
int		put_twod_size(t_list *lst);
char	**put_twod_array(t_list **lst);
void	expander_init(t_list **lst, char *quotes, int *i);

# endif
