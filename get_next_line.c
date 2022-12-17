/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:11:01 by tmarts            #+#    #+#             */
/*   Updated: 2022/12/17 19:20:02 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	next_line_found(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			i++;
			return (i);
		}
		i++;
	}
	return (0);
}

char	*gnl_copier(char *str, size_t len)
{
	char	*dst;

	if(!str)
		return(NULL);
	dst = malloc((len + 1) * sizeof(char));
	if (!dst)
	{
		free(str);
		return (NULL);
	}
	ft_strlcpy(dst, str, len + 1);
	return (dst);
}

// char	*reader(int fd, int buffer)
// {
// 	char	*buf;
// 	size_t	have_read;

// 	buf = malloc((buffer + 1) * sizeof(char));
// 	if (!buf)
// 		return (NULL);
// 	buf[buffer]= 0;
// 	have_read = read(fd, buf, buffer);
// 	if (have_read <= 0)
// 	{
// 		free (buf);
// 		return (0);
// 	}
// 	return (buf);
// }

char	*get_next_line(int fd)
{
	static char	leftovers[BUFFER_SIZE];
	char		*buf;
	char		*current;
	int			len;
	int			have_read;

	buf = NULL;
	len = (next_line_found(leftovers));
	// printf("%d", len);
	if (len > 0)
	{
		current = gnl_copier(leftovers, len);
		// printf("current in the beginning is: %s\n", current);
		ft_strlcpy(leftovers, leftovers + len, BUFFER_SIZE - len + 1);
		return (current);
	}
	if (len == 0)
	{
		current = gnl_copier(leftovers, ft_strlen(leftovers));
		// printf("leftoverlen is: %zu", ft_strlen(leftovers));
		// printf("current in the beginning is: %s\n", current);
		if(!buf)
		{
			buf = malloc((BUFFER_SIZE + 1) * sizeof(char)); //
			if (!buf)
				return (NULL);
			buf[BUFFER_SIZE] = 0;
		}	
		have_read = read(fd, buf, BUFFER_SIZE);
		// printf("buffer is: %s", buf);
		// printf("have_read is is: %d", have_read);
		if (have_read < 0)
		{
			free (buf);
			free(current);
			return (0);
		}
		if (have_read == 0)
		{
			free (buf);
			free (current);
			return (0);
		}
		len = next_line_found(buf);
		while (len == 0)
		{
			current = ft_strljoin(current, buf, have_read);
			// read(fd, buf, BUFFER_SIZE);
			have_read = read(fd, buf, BUFFER_SIZE);
			if (have_read <= 0)
			{
				free (buf);
				free(current);
				return (0);
			}
			len = next_line_found(buf);
			// printf("len is %d\n", len);
		}
		if (len > 0)
		{
			current = ft_strljoin(current, buf, len);
			ft_strlcpy(leftovers, buf + len, BUFFER_SIZE - len + 1);
			// printf("leftovers are: %s\n", leftovers);
			free(buf);
			return (current);
		}
		return (current);//??
	}
	return (0);
}
