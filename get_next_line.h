/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:50:45 by tmarts            #+#    #+#             */
/*   Updated: 2022/12/21 21:19:50 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h> // removeee!!

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 22
# endif

/*get_next_line*/
char	*get_next_line(int fd);
int		next_line_found(char *str);
char	*reader(int fd, char *line, char **leftovers);
char	*read_initiate(int fd);

/*utils*/
size_t	ft_strlen(const char *s);
char	*ft_strljoin(char *s1, char *s2, int len_s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strndup(const char *str, size_t len);

#endif