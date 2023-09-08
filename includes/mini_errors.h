/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_errors.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 13:00:28 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/07 10:43:29 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINI_ERRORS
# define MINI_ERRORS

typedef enum
{
	S_PIPE,
	S_WORD,
	S_REDIRECT
} t_syntax_type;

typedef enum
{
	SYNTAX_ERROR,
	CMD_NOT_FOUND,
	NO_SUCH_PROGRAM,
	PERMISSION_DENIED_PROG,
	NO_SUCH_FILE,
	PERMISSION_DENIED_FILE,
	SUCCESS
} t_exec_error;

// syntax_error
void	syntax_error(void);
void	exec_error(void);
void	exec_error_msg(void);
void	error_printer(void);

#endif
