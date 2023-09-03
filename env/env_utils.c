/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 18:37:31 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/02 19:03:15 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

void	env_list_clear(t_env *env)
{
	t_env	*head;

	if (!env)
		return ;
	head = env;
	while (head)
	{
		head = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = head;
	}
}
