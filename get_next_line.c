/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:11:01 by tmarts            #+#    #+#             */
/*   Updated: 2022/12/18 22:10:16 by tmarts           ###   ########.fr       */
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

	if (!str)
		return (NULL);
	dst = malloc((len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, str, len + 1);
	return (dst);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = s;
	i = 0;
	while (i < n - 1)
	{
		ptr[i] = 0;
		i++;
	}
}

char	*get_next_line(int fd)
{
	static char	leftovers[BUFFER_SIZE];
	char		*buf;
	char		*current;
	int			len;
	int			have_read;

	buf = NULL;
	len = (next_line_found(leftovers));
	if (len > 0)
	{
		current = gnl_copier(leftovers, len);
		if (current == 0)
			return (0);
		ft_strlcpy(leftovers, leftovers + len, BUFFER_SIZE - len + 1);
		free (buf);
		return (current);
	}
	if (len == 0)
	{
		current = gnl_copier(leftovers, ft_strlen(leftovers));
		if (current == 0)
			return (0);
		if(!buf)
		{
			buf = malloc((BUFFER_SIZE + 1) * sizeof(char)); //
			if (!buf)
			{
				free (current);
				return (NULL);
			}
			buf[BUFFER_SIZE] = 0;
		}	
		have_read = read(fd, buf, BUFFER_SIZE);
		if (have_read < 0)
		{
			free (buf);
			free (current);
			ft_bzero(leftovers, BUFFER_SIZE);
			return (0);
		}
		if (have_read == 0)
		{
			free (buf);
			free (current);
			return (0);
		}
		buf[have_read] = 0;
		len = next_line_found(buf);
		while (len == 0)
		{
			current = ft_strljoin(current, buf, have_read);
			if (have_read < BUFFER_SIZE)
			{
				free (buf);
				return (current);
			}
			have_read = read(fd, buf, BUFFER_SIZE);
			if (have_read < 0)
			{
				free (buf);
				free (current);
				ft_bzero(leftovers, BUFFER_SIZE);
				return (0);
			}
			if (have_read == 0)
			{
				free (buf);
				return (current);
			}
			buf[have_read] = 0;
			len = next_line_found(buf);
		}
		if (len > 0)
		{
			current = ft_strljoin(current, buf, len);
			ft_strlcpy(leftovers, buf + len, BUFFER_SIZE - len + 1);
			free(buf);
			return (current);
		}
		free (buf);
		return (current);//??
	}
	free (buf);
	// free (current);
	return (0);
}


// char	*get_next_line(int fd)
// {
// 	static char	leftovers = NULL;
// 	char		*buf;
// 	char		*current;
// 	int			len;
// 	int			have_read;

// 	buf = NULL:
	
// 	while ()
	
// }
// /* reader is used when there is no new line 
// and the leftovers and the content of leftovers has
// been duplicated into the current string - the variable char *line*/

// char	*reader(int fd, char *line, char *leftovers)
// {
// 	char	*buf;
// 	int		read_return;
// 	int		len;

// 	buf = malloc(BUFFER_SIZE + 1 * sizeof(char));
// 	if (!buf)
// 		return (free(line), NULL);
// 	read_return = read(fd, buf, BUFFER_SIZE);
// 	if (read_return <= 0)
// 	{
// 		free(buf);
// 		ft_bzero(leftovers, BUFFER_SIZE);
// 		free (line);
// 		return (0);
// 	}
// 	buf[read_return] = 0;
// 	while (next_line_found(buf) == 0)
// 	{
// 		if (read_return < 0)
// 		{
// 			free(buf);
// 			free (line);
// 			ft_bzero(leftovers, BUFFER_SIZE);
// 			return (0);
// 		}
// 		if (read_return == 0)
// 		{
// 			ft_bzero(leftovers, BUFFER_SIZE);
// 			free(buf);
// 			return (line);
// 		}
// 		buf[read_return] = 0;
// 		line = ft_strljoin(line, buf, read_return);
// 		read_return = read(fd, buf, BUFFER_SIZE);
// 	}
// 	len = next_line_found(buf);
// 	line = ft_strljoin(line, buf, len);
// 	ft_strlcpy(leftovers, buf + len, BUFFER_SIZE - len + 1);
// 	free(buf);
// 	return (line);
// }

// char	*get_next_line(int fd)
// {
// 	static char	leftovers[BUFFER_SIZE];
// 	char		*current;
// 	int			len;

// 	len = (next_line_found(leftovers));
// 	if (len > 0)
// 	{
// 		current = gnl_copier(leftovers, len);
// 		if (current == 0)
// 			return (0);
// 		ft_strlcpy(leftovers, leftovers + len, BUFFER_SIZE - len + 1);
// 		return (current);
// 	}
// 	else
// 	{
// 		current = gnl_copier(leftovers, ft_strlen(leftovers));
// 		if (current == 0)
// 			return (0);
// 		current = reader(fd, current, leftovers);
// 		if (current == 0)
// 			return (0);
// 		return (current);
// 	}
// }

// char	*reader(int fd, int buffer)
// {
// 	char	*buf;
// 	size_t	have_read;

// 	have_read = read(fd, buf, buffer);
// 	if (have_read < 0)
// 	{
// 		free (buf);
// 		return (0);
// 	}
	
// 	return (buf);
// }

