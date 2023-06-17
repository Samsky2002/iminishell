/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:57:54 by oakerkao          #+#    #+#             */
/*   Updated: 2023/06/17 19:13:11 by oakerkao         ###   ########.fr       */
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

void	expanded()
{
	t_node	*node;

	node = g_minishell.node;
	while (node)
	{
		while (node->args)
		{
			expander(node->args->arg);
			node->args = node->args->next;
		}
		node = node->next;	
	}
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
		if (!red || !*red)
			continue;
		tokenizer(red);
		syntax_error();
		if (!g_minishell.s_error)
		{
			parse();
			//print_list();
		}
		//expanded();
		exec();
		add_history(red);
	}
}
