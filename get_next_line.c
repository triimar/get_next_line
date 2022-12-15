/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:11:01 by tmarts            #+#    #+#             */
/*   Updated: 2022/12/15 22:48:07 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		ptr[i] = 0;
		i++;
	}
	return ((void *)ptr);
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
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize != 0)
	{
		while (i < dstsize - 1 && src[i] != 0)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	while (src[i] != 0)
		i++;
	return (i);
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


// char	*gnl_initiate(int buffer_size)
// {
// 	char	*buf;

// 	buf = malloc(buffer_size + 1 * sizeof(char));
// 	if (!buf)
// 		return (NULL);
// 	if (read(fd, buf, buffer) <= 0)
// 	{
// 		free (buf);
// 		return (0);
// 	}
// 	return (buf);
// }

int	next_line_found(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*gnl_copier(char *str, size_t len)
{
	char	*dst;

	dst = malloc((len + 1) * sizeof(char));
	if (!dst)
	{
		free(str);
		return (NULL);
	}
	ft_memcpy(dst, str, len);
	*(dst + len) = 0;
	return (dst);
}

char	*reader(int fd, int buffer)
{
	char	*buf;
	size_t	have_read;

	buf = ft_calloc(buffer + 1, sizeof(char));
	if (!buf)
		return (NULL);
	have_read = read(fd, buf, buffer);
	if (have_read <= 0)
	{
		free (buf);
		return (0);
	}
	return (buf);
}


char	*get_next_line(int fd)
{
	static char	leftovers[BUFFER_SIZE + 1];
	char		*buf;
	char		*current;
	char		*temp;
	int			len;

	len = (next_line_found(leftovers));
	// printf("len is %d\n", len);
	if (len > 0)
	{
		current = gnl_copier(leftovers, len);
		ft_strlcpy(leftovers, leftovers + len, BUFFER_SIZE - len);//free something
		return (current);
	}
	else
	{
		current = gnl_copier(leftovers, ft_strlen(leftovers));
		buf = reader(fd, BUFFER_SIZE);
		if (!buf)
			return (0);
		len = next_line_found(buf);
		while (len == 0)
		{
			current = ft_strjoin(current, buf);
			read(fd, buf, BUFFER_SIZE) <= 0;
			len = next_line_found(buf);
			printf("len is %d\n", len);
		}
		if (len > 0)
		{
			temp = gnl_copier(buf, len);
			current = ft_strjoin(current, temp);
			free(temp);
			ft_strlcpy(leftovers, buf + len, BUFFER_SIZE - len);
			printf("leftovers are: %s\n", leftovers);
			free(buf);
			return (current);
		}
		
	//what happens when buffer_size does not contain newline			
	}
	return (0);
}

// char	*get_next_line(int fd)
// {
// 	static char	*input;
// 	char		*next_line;
// 	// char		*buf;
// 	// char		*temp;
// 	int			line_len;

// 	if (!input)
// 	{
// 		input = reader(fd, BUFFER_SIZE);
// 		if (!input)
// 			return (0);
// 		// printf("input is: %s\n", input);
// 	}
// 	line_len = (next_line_found(input));
// 	// printf("line_len is %d\n", line_len);
// 	// if (line_len == 0)
// 	// {
// 	// 	buf = reader(fd, BUFFER_SIZE);
// 	// 	if (!buf)
// 	// 		return (0);
// 	// 	temp = gnl_copier(input, (ft_strlen(input) + 1));
// 	// 	if (!temp)
// 	// 	{
// 	// 		free(input);
// 	// 		return (NULL);
// 	// 	}
// 	// 	input = ft_strjoin(temp, buf);
// 	// 	free(temp);
// 	// 	free(buf);
// 	// 	get_next_line(fd);
// 	// }
// 	next_line = gnl_copier(input, line_len);
// 	if (!next_line)
// 	{
// 		free(input);
// 		return (NULL);
// 	}
// 	input = gnl_copier(input + line_len, BUFFER_SIZE - line_len);
// 	if (!next_line)
// 	{
// 		free(input);
// 		return (NULL);
// 	}
// 	printf("output is: %s\n", input);
// 	return (next_line);
// }
