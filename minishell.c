/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:57:54 by oakerkao          #+#    #+#             */
/*   Updated: 2023/05/14 18:36:30 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	find_type(int i)
{
	if (i == 0)
		printf("%s\n", "T_WORD");
	else if (i == 1)
		printf("%s\n", "T_PIPE");
	else if (i == 2)
		printf("%s\n", "T_HERE_DOC");
	else if (i == 3)
		printf("%s\n", "T_IN");
	else if (i == 4)
		printf("%s\n", "T_OUT");
	else if (i == 5)
		printf("%s\n", "T_APPEND");
	else if (i == 6)
		printf("%s\n", "T_NULL");
}
int main(int argc, char *argv[], char *enviro[])
{
	char	*red;
	t_token	*token;
	char	**list;

	get_env_list(enviro);
	/*char	*args1[] = {"export", "new=", NULL};
	export(args1);
	char	*args[] = {"export", NULL};
	export(args);
	printf("************************h\n");
	env();*/
	while (1)
	{
		red = readline("> ");
		list = expander(red);
		while (list && *list)
		{
			printf("%s\n", *list);	
			list++;
		}
		add_history(red);
	}
}
