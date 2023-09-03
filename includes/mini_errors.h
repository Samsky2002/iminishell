/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_errors.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 13:00:28 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/02 13:45:46 by oakerkao         ###   ########.fr       */
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

// syntax_error
void	syntax_error(void);

#endif
