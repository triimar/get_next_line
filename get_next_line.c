/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:50:41 by tmarts            #+#    #+#             */
/*   Updated: 2022/12/13 13:16:53 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	size;
	size_t	s_len;
	char	*sub;

	s_len = ft_strlen(s);
	size = len;
	if (s_len <= start)
		size = 0;
	else if (s_len < len || s_len < len + start)
		size = s_len - start;
	sub = (char *)malloc((size + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < size)
	{
		sub[i] = s[start + i];
		i++;
	}
	if (i == size)
			sub[i] = '\0';
	return (sub);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	string = malloc(s1_len + s2_len + 1);
	if (!string)
		return (NULL);
	while (*s1 != 0)
		*string++ = *s1++;
	while (*s2 != 0)
		*string++ = *s2++;
	*string = '\0';
	return (string - s1_len - s2_len);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*to;
	char	*from;

	if (dst == 0 && src == 0)
		return (0);
	to = (char *)dst;
	from = (char *)src;
	while (n != 0)
	{
		*to = *from;
		to++;
		from++;
		n--;
	}
	return (dst);
}

char	*get_next_line(int fd)
{
	char	*buf;
	char	*next_line;
	int		i;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = 0;
	if (read (fd, buf, BUFFER_SIZE + 1) <= 0)
	{
		free (buf);
		return (0);
	}
	i = 0;
	while (buf[i] != '\n')
	{
		if (buf[i] != 0)
			
		i++;
	}
	printf("index is: %d\n", i);
	next_line = malloc((i + 2) * sizeof(char));
	if (!next_line)
	{
		free(buf);
		return (NULL);
	}
	next_line[i + 1] = 0;
	ft_memcpy(next_line, buf, i + 1);
	free(buf);
	return (next_line);
}


// need to deal with leftovers 
// need to deal with the option that newline is not within buffer