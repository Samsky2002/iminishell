/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:53:42 by oakerkao          #+#    #+#             */
/*   Updated: 2023/05/13 13:24:58 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char	*word_cpy(char *str, int buff_size, int len)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(buff_size + 1);
	while (i < len)
	{
		if (str[i] == '\'' || str[i] == '"')
			i++;
		else
		{
			result[j] = str[i];
			i++;
			j++;
		}
	}
	result[j] = '\0';
	return (result);
}

int	word_token(t_token **head, char *str)
{
	int		i;
	char	*result;
	t_list	*list;
	char	quotes;
	int len;

	i = 0;
	quotes = 0;
	len = 0;
	while (str && ((quotes != 0 && str[i]) || (str[i] != '|' && str[i] != '>' && str[i] != '<' && str[i] && str[i] != ' ')))
	{
		if ((str[i] == '\'' || str[i] == '"') && quotes == 0)
			quotes = str[i];
		else if (quotes == str[i])
			quotes = 0;
		i++;
	}
	if (quotes != 0)
	{
		printf("error\n");
		exit(0);
		return (i);
	}
	result = malloc(i + 1); 
	ft_strlcpy(result, str, i + 1);
	add_token(head, new_token(result, T_WORD));
	return (i);
}

int	space_skip(t_token **head, char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

int	here_doc_token(t_token **head, char *str)
{
	if (str[0] == '<' && str[1] == '<')
	{
		add_token(head, new_token("<<", T_HERE_DOC));	
		return (2);
	}
	return (0);
}

int	redirect_token(t_token **head, char *str)
{
	if (str[1] == '<')
		return (0);
	else if (str[0] == '<')
		add_token(head, new_token("<", T_IN));
	else if (str[0] == '>' && str[1] != '>')
		add_token(head, new_token(">", T_OUT));
	else if (str[0] == '>' && str[1] == '>')
	{
		add_token(head, new_token(">>", T_APPEND));
		return (2);
	}
	return (1);
}

int	pipe_token(t_token **head)
{
	add_token(head, new_token("|", T_PIPE));
	return (1);
}

t_token	*tokenizer(char *line)
{
	t_token	*token;

	token = NULL;
	while (line && *line)
	{
		if (ft_strncmp(line, "|", 1) == 0)
			line += pipe_token(&token);
		else if (ft_strncmp(line, "<<", 2) == 0)
			line += here_doc_token(&token, line);
		else if ((ft_strncmp(line, ">", 1) == 0) || (ft_strncmp(line, "<", 1) == 0))
			line += redirect_token(&token, line);
		else if (ft_strncmp(line, " ", 1) == 0)
			line += space_skip(&token, line);
		else
			line += word_token(&token, line);
	}
	add_token(&token, new_token(NULL, T_NULL));
	return (token);
}

/*int main(int argc, char *argv[])
{
	t_token *head;
	t_token	*get;

	head = tokenizer(readline("b3bola# "));
	while (head)
	{
		printf("%s\n", head->token);	
		head = head->next;
	}
}*/
