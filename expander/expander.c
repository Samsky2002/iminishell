/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:04:54 by oakerkao          #+#    #+#             */
/*   Updated: 2023/06/17 20:17:39 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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
	/*i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}*/
	return (arr);
}

char	*get_var_name(char *str)
{
	int		i;
	char	*result;

	i = 1;
	if (!str || !*str)
		return (0);
	if (str && str[0] && !((str[0] >= 'a' && str[0] <= 'z') || \
				(str[0] >= 'A' && str[0] <= 'Z') || \
				(str[0] == '_')))
	{
		if (str[0] == '$')
			return (0);
		result = malloc(2);
		ft_strlcpy(result, str, 2);
		return (result);
	}
	while (str[i] && ((str[i] >= '0' && str[i] != '9') || \
				(str[i] >= 'a' && str[i] <= 'z') || \
				(str[i] >= 'A' && str[i] <= 'Z') || \
				str[i] == '_'))
		i++;	
	result = malloc(i + 1);
	ft_strlcpy(result, str, i + 1);
	return (result);
}

int	has_space(char *str, int type)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(str);
	if (type == 0)
	{
		while (str[i] == ' ')	
			i++;
		if (i == len)
			return (1);
	}
	if (type == -1)
	{
		if (*str == ' ')		
			return (1);
	}
	else if (type == 1)
	{
		if (str[len - 1] == ' ')		
			return (1);
	}
	return (0);
}

int	expand_variable(t_list **lst, t_list **tmp, char *str)
{
	int	i;
	char	*var;
	char	**splited;
	t_env	*node;

	i = 0;
	var = get_key(get_var_name(str + 1));
	node = get_node(get_var_name(str + 1));
	if (node)
	{
		if (!has_space(node->value, 0))
			splited = ft_split(node->value, ' ');
		else if (has_space(node->value, 0))
		{
			ft_lstadd_back(lst, ft_lstnew(NULL));
			(*tmp) = (*tmp)->next;
			return (ft_strlen(var));	
		}
		if ((*tmp)->content && (has_space(node->value, -1) == 0 || *(char *)(*tmp)->content == '\0'))
		{
			//printf("here1\n");
			(*tmp)->content = ft_strjoin((*tmp)->content, *splited);
		}
		else if ((*tmp)->content && has_space(node->value, -1))
		{
			//printf("here2\n");
			ft_lstadd_back(lst, ft_lstnew(NULL));
			(*tmp) = (*tmp)->next;
			(*tmp)->content = ft_strdup(*splited);
		}
		else
		{
			//printf("here3\n");
			(*tmp)->content = ft_strdup(*splited);
		}
		splited++;
		while (*splited)
		{
			ft_lstadd_back(lst, ft_lstnew(NULL));
			(*tmp) = (*tmp)->next;
			(*tmp)->content = ft_strdup(*splited);
			splited++;
		}
		if (has_space(node->value, 1))
		{
			ft_lstadd_back(lst, ft_lstnew(NULL));
			(*tmp) = (*tmp)->next;
		}
	}
	return (ft_strlen(get_var_name(str + 1)));
}

int	expand_quoted_variable(t_list **lst, t_list **tmp, char *str)
{
	int	i;
	char	*var;
	char	**splited;
	t_env	*node;

	i = 0;
	var = get_key(get_var_name(str + 1));
	node = get_node(get_var_name(str + 1));
	if (node)
	{
		if ((*tmp)->content)	
			(*tmp)->content = ft_strjoin((*tmp)->content, node->value);
		else
			(*tmp)->content = ft_strdup(node->value);
	}
	return (ft_strlen(var));
}

char	**expander(char *str)
{
	int		i;
	char	quotes;
	t_list	*lst;
	t_list	*tmp;

	i = 0;
	quotes = 0;
	lst = NULL;
	ft_lstadd_back(&lst, ft_lstnew(NULL));
	tmp = lst;
	while (str && str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && !quotes)
		{
			lst->content = char_join(lst->content, '\0');
			quotes = str[i];
		}
		else if (str[i] == quotes)
			quotes = 0;
		else if (str[i] == '$' && quotes == 0)
		{
			i += expand_variable(&lst, &tmp, str + i);
			if (str[i] == '$')
				tmp->content = char_join(tmp->content, str[i]);
		}
		else if (str[i] == '$' && quotes == '"')
			i += expand_quoted_variable(&lst, &tmp, str + i);
		else
			tmp->content = char_join(tmp->content, str[i]);
		i++;
	}
	return (put_twod_array(&lst));
}
