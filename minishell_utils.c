/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:54:33 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/11 17:55:22 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*char_join_help(char *str, char c)
{
	char	*result;

	if (!str && c == '\0')
	{
		result = malloc(1);
		result[0] = '\0';
		return (result);
	}
	else if (!str)
	{
		result = malloc(2);
		result[0] = c;
		result[1] = '\0';
		return (result);
	}
	return (0);
}

char	*char_join(char *str, char c)
{
	char	*result;
	int		len;
	int		i;
	char	*help;

	i = 0;
	help = char_join_help(str, c);
	if (help)
		return (help);
	if (c == '\0')
		return (str);
	len = ft_strlen(str);
	result = malloc(len + 2);
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = c;
	result[i + 1] = '\0';
	free(str);
	return (result);
}

void	free_twod_array(char **arr)
{
	char	**tmp;

	tmp = arr;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(arr);
}

int	put_twod_size(t_list *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		if (lst->content)
			len++;
		lst = lst->next;
	}
	return (len);
}

char	**put_twod_array(t_list **lst)
{
	int		len;
	char	**arr;
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *lst;
	len = put_twod_size(tmp);
	arr = malloc((len + 1) * sizeof(char *));
	while (tmp)
	{
		if (tmp->content)
		{
			arr[i] = ft_strdup(tmp->content);
			i++;
		}
		tmp = tmp->next;
	}
	arr[i] = NULL;
	ft_lstclear(lst, free);
	return (arr);
}

/*void	print_list(t_node *node)
{
	int	i;

	i = 0;
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

void	print_tokens(t_token *token)
{
	while (token)
	{
		printf("--------------------START----------------\n");
		printf("----------TYPE---------\n");
		find_type(token->type);
		printf("----------END_TYPE---------\n");
		printf("----------TOKEN---------\n");
		printf("%s\n", token->token);
		printf("----------END_TOKEN---------\n");
		printf("--------------------END----------------\n");
		token = token->next;
	}
}*/
