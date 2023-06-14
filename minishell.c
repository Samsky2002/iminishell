/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:57:54 by oakerkao          #+#    #+#             */
/*   Updated: 2023/06/14 18:28:40 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	print_list()
{
	t_node	*node;
	int	i;

	i = 0;
	node = g_minishell.node;
	while (node)	
	{
		printf("-----------NODE-------------\n");
		while (node->args)	
		{
			printf("%d: args : %s\n", i, node->args->arg);
			node->args = node->args->next;
		}
		while (node->redirect)	
		{
			printf("%d: redirect : %s\n", i, node->redirect->path);
			find_type(node->redirect->type);
			node->redirect = node->redirect->next;
		}
		printf("-----------END-------------\n");
		i++;
		node = node->next;
	}
}

void	find_type(int i)
{
	if (i == 0)
		printf("-----%s-----\n", "T_WORD");
	else if (i == 1)
		printf("-----%s-----\n", "T_PIPE");
	else if (i == 2)
		printf("-----%s-----\n", "T_HERE_DOC");
	else if (i == 3)
		printf("-----%s-----\n", "T_IN");
	else if (i == 4)
		printf("-----%s-----\n", "T_OUT");
	else if (i == 5)
		printf("-----%s-----\n", "T_APPEND");
	else if (i == 6)
		printf("-----%s-----\n", "T_NULL");
}
int main(int argc, char *argv[], char *enviro[])
{
	char	*red;
	t_token	*token;
	char	**list;

	get_env_list(enviro);
	while (1)
	{
		red = readline("> ");
		tokenizer(red);
		parse();
		print_list();
		add_history(red);
	}
}
