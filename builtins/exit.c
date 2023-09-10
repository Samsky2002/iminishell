/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:41:56 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/09 16:30:22 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	check_long(unsigned long long res, int sign)
{
	if (res > 9223372036854775807 && sign == 1)
		return (0);
	else if (res > 9223372036854775808UL && sign == -1)
		return (0);
	return (1);
}

int	is_valid(char *str, int sign)
{
	int					i;
	unsigned long long	res;

	i = 0;
	res = 0;
	while (str[i])	
	{
		if (res > res * 10 + (str[i] - 48))	
			return (0);
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (check_long(res ,sign));
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))	
			return (0);
		i++;
	}
	return (1);
}

int	check_exit_arg(char *str, t_minishell *minishell)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	if (is_number(str + i) == 0 || is_valid(str + i, sign) == 0)
	{
		minishell->mini_error = NUMERIC_ARG_REQ;
		exec_error_msg(minishell);
		exec_error(minishell);
		exit(minishell->exit_s);
	}
	return (ft_atoi(str));
}

void	ft_exit(char **args, t_minishell *minishell)
{
	int	exit_value;

	if (args[1])
	{
		if (check_exit_arg(args[1], minishell) && !args[2])
		{
			exit_value = check_exit_arg(args[1], minishell);
			exit(exit_value);
		}
		if (args[2])
		{
			minishell->mini_error = TOO_MANY_ARGS;
			//exec_error_msg();
			exec_error(minishell);
			return ;
		}
	}
	exit(minishell->exit_s);
}
// understand this code
