/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:11:01 by tmarts            #+#    #+#             */
/*   Updated: 2022/12/26 21:44:59 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
char	*read_initiate(int fd)
Allocates and returns a null terminated string 
and returns the string after single implementation 
of read(). Returns NULL in case of an error.
*/
char	*read_initiate(int fd)
{
	char	*buf;
	ssize_t	read_return;

	buf = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buf)
		return (NULL);
	read_return = read(fd, buf, BUFFER_SIZE);
	if (read_return == -1)
	{
		free (buf);
		return (NULL);
	}
	buf[read_return] = 0;
	return (buf);
}

char	*free_reader(char *buf, char *line)
{
	if (line)
		free(line);
	if (buf)
		free(buf);
	return (NULL);
}

/*
char	*reader (int fd, char *line, char **leftovers)
Reads from fd, finding the first occurrence of '/n' and returning the
new (or final) line found in the process of implementing read().
Uses malloc () and free () to join the substrings that contain no '\n'.
When '\n' is found - uses ft_strljoin() to create the final string to 
be returned and allocates with use of strndup()the unexamined part 
of the string to the static pointer "leftovers".
Returns "line" or NULL in case of error
*/
char	*reader(int fd, char *line, char **leftovers)
{
	char	*buf;
	ssize_t	read_return;
	size_t	len;

	buf = read_initiate(fd);
	if (!buf)
		return (free_reader(buf, line));
	read_return = ft_strlen(buf);
	while (ft_linelen(buf) == 0 && read_return != 0)
	{
		line = ft_strljoin(line, buf, read_return);
		read_return = read(fd, buf, BUFFER_SIZE);
		if (line == 0 || read_return == -1)
			return (free_reader(buf, line));
		buf[read_return] = 0;
	}
	len = ft_linelen(buf);
	line = ft_strljoin(line, buf, len);
	if (line != 0 && len != (size_t)read_return)
	{
		*leftovers = ft_strndup(buf + len, read_return - len + 1);
		if (!*leftovers)
			return (free_reader(buf, line));
	}	
	return (free(buf), line);
}

char	*free_leftovers(char **left)
{
	free(*left);
	*left = NULL;
	return (NULL);
}

/*
char	*get_next_line(int fd)
Returns a line read from a file descriptor.
Process: 1) Checks the static variable "leftovers". Proceeds to read from fd if 
the pointer is NULL. 2) Checks the content of static variable - returns the new 
line if it is found in the static variable. 3) If '\n' is not found in a static 
variable duplicates it to the return string and implements reader() function to 
find the next occurrence of the '/n' in the fd.
*/
char	*get_next_line(int fd)
{
	static char	*left;
	char		*line;
	size_t		len;

	if (left == NULL)
		return (reader(fd, NULL, &left));
	len = (ft_linelen(left));
	if (len > 0)
	{
		line = ft_strndup(left, len);
		if (!line)
			return (free_leftovers(&left));
		if (len == ft_strlen(left))
			free_leftovers(&left);
		else
			ft_strlcpy(left, left + len, ft_strlen(left) - len + 1);
		return (line);
	}
	line = ft_strndup(left, ft_strlen(left));
	free_leftovers(&left);
	if (line == 0)
		return (NULL);
	return (reader(fd, line, &left));
}
