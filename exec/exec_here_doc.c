/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:34:17 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/10 19:22:34 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	got_here_doc(t_exec_redirect *redirect, t_minishell *minishell)
{
	while (redirect)
	{
		if (redirect->type == T_HERE_DOC)
			minishell->here_doc = minishell->here_doc->next;
		redirect = redirect->next;
	}
}

void	here_doc_traverse(t_minishell *minishell)
{
	t_fd	*list;
	t_fd	*tmp;
	t_exec	*exec;
	t_exec_redirect	*redirect;

	exec = minishell->exec;
	list = NULL;
	while (exec)
	{
		redirect = exec->redirect;
		while (redirect)
		{
			if (redirect->type == T_HERE_DOC)
				here_doc(&list, redirect->list[0], minishell);
			redirect = redirect->next;
		}
		exec = exec->next;
	}
	minishell->here_doc = list;
}

int	skip_word(char *str)
{
	int		i;
	char	quotes;

	i = 0;
	quotes = 0;
	while ((quotes || str[i] != ' ') && str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && quotes == 0)
			quotes = str[i];
		else if (str[i] == quotes)
			quotes = 0;
		i++;
	}
	return (i);
}

char	*word_join(char *str, char **arr)
{
	char	*result;
	int		i;
	int		j;
	int		k;
	int		count;

	i = 0;
	result = NULL;
	if (str)
		result = ft_strdup(str);
	while (arr && arr[i])
	{
		if (result)
			result = ft_strjoin(result, arr[i]);
		else
			result = ft_strdup(arr[i]);
		i++;
	}
	return (result);
}

char	*expand_here_doc(char *line, t_minishell *minishell)
{
	char	*result;	
	char	**arr;
	int		i;

	i = 0;
	result = NULL;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			arr = expander(line + i, minishell);
			result = word_join(result, arr);
			i += skip_word(line + i);
			continue ;
		}
		else if (line[i] == ' ')
			result = char_join(result, line[i]);
		i++;
	}
	return (result);
}

char	*get_end(char *delimiter)
{
	char	*end;

	end = NULL;
	if (ft_strchr(delimiter, '"'))
		end = ft_strtrim(delimiter, "\"");
	else if (ft_strchr(delimiter, '\''))
		end = ft_strtrim(delimiter, "'");
	else
		end = ft_strdup(delimiter);
	return (end);
}

void	here_doc(t_fd **list, char *delimiter, t_minishell *minishell)
{
	char	*red;
	int		p[2];
	char	*end;

	end = get_end(delimiter);
	pipe(p);
	while (1)
	{
		red = readline("here_doc>");
		if (!red)
			break ;
		if (!ft_strchr(delimiter, '\'') && !ft_strchr(delimiter, '"'))
			red = expand_here_doc(red, minishell);
		if (ft_strcmp(red, end) == 0)
			break ;
		ft_putstr_fd(red, p[1]);
		ft_putstr_fd("\n", p[1]);
		free(red);
	}
	close(p[1]);
	add_here_list(list, new_here_list(p[0]));
}
