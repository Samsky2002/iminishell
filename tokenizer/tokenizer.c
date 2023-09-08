/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:53:42 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/07 10:51:35 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_token(t_token **token, char *line)
{
	int		i;
	char	quotes;
	char	*result;

	i = 0;
	quotes = 0;
	result = NULL;
	while (line && line[i] && (quotes || (line[i] != '>' && \
					line[i] != '<' && line[i] != '|' && line[i] != ' ')))
	{
		if ((line[i] == '\'' || line[i] == '"') && quotes == 0)
			quotes = line[i];
		else if (line[i] == quotes)
			quotes = 0;
		result = char_join(result, line[i]);
		i++;
	}
	if (quotes)
		g_minishell.mini_error = SYNTAX_ERROR;
	add_token(token, new_token(result, T_WORD));
	return (i);
}

int	space_token(char *line)
{
	int	i;

	i = 0;
	while (line && line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

int	single_char_special_token(t_token **token, t_token_type type)
{
	if (type == T_PIPE)
		add_token(token, new_token(ft_strdup("|"), type));
	else if (type == T_IN)
		add_token(token, new_token(ft_strdup("<"), type));
	else if (type == T_OUT)
		add_token(token, new_token(ft_strdup(">"), type));
	return (1);
}

int	double_char_special_token(t_token **token, t_token_type type)
{
	if (type == T_HERE_DOC)
		add_token(token, new_token(ft_strdup("<<"), type));
	else if (type == T_APPEND)
		add_token(token, new_token(ft_strdup(">>"), type));
	return (2);
}

void	tokenizer(char *line)
{
	t_token	*token;

	token = NULL;
	while (line && *line)
	{
		if (ft_strncmp(line, "|", 1) == 0)
			line += single_char_special_token(&token, T_PIPE);
		else if (ft_strncmp(line, "<<", 2) == 0)
			line += double_char_special_token(&token, T_HERE_DOC);
		else if ((ft_strncmp(line, ">>", 2) == 0))
			line += double_char_special_token(&token, T_APPEND);
		else if (ft_strncmp(line, ">", 1) == 0)
			line += single_char_special_token(&token, T_OUT);
		else if ((ft_strncmp(line, "<", 1) == 0))
			line += single_char_special_token(&token, T_IN);
		else if (ft_strncmp(line, " ", 1) == 0)
			line += space_token(line);
		else
			line += word_token(&token, line);
	}
	g_minishell.token = token;
}
