/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:34:17 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/16 13:36:58 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	write_word(char *str, int fd, t_minishell *minishell)
{
	int		i;
	char	*var_name;
	char	*tmp;
	t_list	*lst;
	t_list	*temp;

	lst = NULL;
	var_name = get_var_name(str + 1);
	tmp = ft_strjoin("$", var_name);
	here_doc_expansion(&lst, minishell, tmp);
	temp = lst;
	while (temp)
	{
		ft_putstr_fd(temp->content, fd);
		temp = temp->next;
	}
	i = ft_strlen(var_name);
	free(var_name);
	free(tmp);
	ft_lstclear(&lst, free);
	return (i);
}

void	expand_here_doc(char *line, t_minishell *minishell, int fd, char *delim)
{
	int		i;
	char	*tmp;
	int		expand;

	i = 0;
	expand = 0;
	if (!ft_strchr(delim, '"') && !ft_strchr(delim, '\''))
		expand = 1;
	tmp = ft_strtrim(line, "\n");
	line = tmp;
	while (line[i])
	{
		if (line[i] == '$' && expand)
			i += write_word(line + i, fd, minishell);
		else
			ft_putchar_fd(line[i], fd);
		i++;
	}
	free(tmp);
	ft_putstr_fd("\n", fd);
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

	g_sig[3] = dup(0);
	end = get_end(delimiter);
	pipe(p);
	g_sig[2] = 1;
	while (1)
	{
		ft_putstr_fd("here_doc> ", 1);
		red = get_next_line(g_sig[3]);
		if (!red)
			break ;
		if (ft_strncmp(red, end, ft_strlen(end)) == 0)
			break ;
		expand_here_doc(red, minishell, p[1], delimiter);
		free(red);
	}
	if (g_sig[4])
		minishell->exit_s = g_sig[4];
	free(end);
	g_sig[2] = 0;
	close(p[1]);
	add_here_list(list, new_here_list(p[0]));
}
