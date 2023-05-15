/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:46:21 by oakerkao          #+#    #+#             */
/*   Updated: 2023/04/06 01:02:25 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# include <stdlib.h>
# include <unistd.h>
# include <sys/syslimits.h>
# include "libft.h"

char	*get_next_line(int fd);
char	*str_dup(char *str);
char	*str_save(char *str);
char	*str_rem(char *str);
char	*str_res(char *str1, char *str2);
char	*read_check(int fd, char *result);

#endif
