/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:14:46 by oakerkao          #+#    #+#             */
/*   Updated: 2023/05/03 12:16:57 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef REDIRECTION
# define REDIRECTION

# include <fcntl.h>
# include <readline/readline.h>
# include "../libft/libft.h"

int	append_file(char *file);
int	outfile(char *file);
int	infile(char *file);

/*pipe*/
void	piping(char **arg1, char **arg2);
int	here_doc(char *delimiter, int fd);
# endif
