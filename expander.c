/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:04:54 by oakerkao          #+#    #+#             */
/*   Updated: 2023/05/14 17:22:32 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*get_var(char *str)
{
	int	i;
	char *result;

	i = 0;
	while (str[i] != '\'' && str[i] != '"' && str[i] != ' ' && str[i])
		i++;
	result = malloc(i + 1);
	ft_strlcpy(result, str, i + 1);
	return (result);
}

char	*char_join(char *str, char c)
{
	char	*result;
	int		len;
	int		i;

	i = 0;
	if (!str)
	{
		result = malloc(2);	
		result[0] = c;
		result[1] = '\0';
		return (result);
	}
	len = ft_strlen(str) + 2;
	result = malloc(len);
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = c;
	result[i + 1] = '\0';
	return (result);
}

int	check_value(t_list **lst, char *str, int i, t_list	**tmpo)
{
	char	**splited;
	char	*tmp;
	t_env	*node;
	int	j;

	j = 1;
	tmp = get_var(str);
	i = 0;
	i += ft_strlen(tmp);
	if (get_node(tmp))
	{
		node = get_node(tmp);
		splited = ft_split(node->value, ' ');
		(*lst)->content = ft_strjoin(2, (*lst)->content, splited[0]);
		while (splited && splited[j])
		{
			ft_lstadd_back(lst, ft_lstnew(splited[j]));
			*tmpo = (*tmpo)->next;
			j++;
		}
	}
	return (i);
}

char	**expander(char *str)
{
	char	quotes;
	int		i;
	t_list	*lst;
	char	**splited;
	t_list	*tmpo;

	i = 0;
	quotes = 0;
	lst = NULL;
	ft_lstadd_back(&lst, ft_lstnew(NULL));
	tmpo = lst;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && quotes == 0)	
			quotes = str[i];
		else if (quotes == str[i])
			quotes = 0;
		else if (str[i] == '$' && quotes != '\'')
			i += check_value(&lst, str + i + 1, i, &tmpo);
		else
			tmpo->content = char_join(tmpo->content, str[i]);
		i++;
	}
	splited = put_twod_array(lst);
	return (splited);
}
