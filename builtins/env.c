/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:29:54 by oakerkao          #+#    #+#             */
/*   Updated: 2023/06/14 15:03:16 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	env(void)
{
	t_env	*list;

	list = g_minishell.list;
	while (list)
	{
		if (list->value != NULL)
			printf("%s=%s\n", list->key, list->value);	
		list = list->next;
	}
}
