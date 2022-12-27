/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:50:45 by tmarts            #+#    #+#             */
/*   Updated: 2022/12/27 15:20:40 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 22
# endif

/*get_next_line*/
char	*read_initiate(int fd);
char	*free_reader(char *buf, char *line);
char	*reader(int fd, char *line, char **leftovers);
char	*null_leftovers(char **leftovers);
char	*get_next_line(int fd);

/*utils*/
size_t	ft_strlen(const char *s);
size_t	ft_linelen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strljoin(char *s1, char *s2, int len_s2);
char	*ft_strndup(const char *str, size_t len);

#endif