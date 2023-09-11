/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_second_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:49:00 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/11 12:00:11 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_next(t_list **lst, t_list **tmp, char **arr)
{
	ft_lstadd_back(lst, ft_lstnew(NULL));
	*tmp = (*tmp)->next;
	free_twod_array(arr);
}
