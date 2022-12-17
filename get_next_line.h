/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:50:45 by tmarts            #+#    #+#             */
/*   Updated: 2022/12/17 19:01:45 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h> // removeee!!

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 60
# endif

/*get_next_line*/
char	*get_next_line(int fd);
int		next_line_found(char *str);
char	*gnl_copier(char *str, size_t len);

/*utils*/
size_t	ft_strlen(const char *s);
char	*ft_strljoin(char *s1, char *s2, int len_s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	*ft_memcpy(void *dst, const void *src, size_t n);


#endif