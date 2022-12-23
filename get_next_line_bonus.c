/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 22:04:20 by tmarts            #+#    #+#             */
/*   Updated: 2022/12/23 23:05:50 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*reader(int fd, char *line, char **leftovers)
{
	char	*buf;
	ssize_t	read_return;
	int		len;

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
	if (line != 0 && len != read_return)
	{
		*leftovers = ft_strndup(buf + len, read_return - len + 1);
		if (!*leftovers)
			return (free_reader(buf, line));
	}	
	return (free(buf), line);
}

char	*free_leftovers(char **leftovers)
{
	free(*leftovers);
	*leftovers = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*leftovers[1024];
	char		*line;
	int			len;

	if (fd < 0 || fd > 1024)
		return (NULL);
	if (leftovers[fd] == NULL)
		return (reader(fd, NULL, &(leftovers[fd])));
	len = (ft_linelen(leftovers[fd]));
	if (len > 0)
	{
		line = ft_strndup(leftovers[fd], len);
		if (line == 0)
			return (free_leftovers(&(leftovers[fd])));
		ft_strlcpy(leftovers[fd], leftovers[fd] + len, BUFFER_SIZE - len + 1);
		return (line);
	}
	line = ft_strndup(leftovers[fd], ft_strlen(leftovers[fd]));
	free_leftovers(&(leftovers[fd]));
	if (line == 0)
		return (NULL);
	return (reader(fd, line, &(leftovers[fd])));
}
