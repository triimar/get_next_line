/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_alt_ver2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 21:40:55 by tmarts            #+#    #+#             */
/*   Updated: 2022/12/23 22:44:50 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_linelen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
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
	if (!buf && line)
		return (free(line), NULL);
	if (!buf)
		return (NULL);
	read_return = ft_strlen(buf);
	while (ft_linelen(buf) == 0 && read_return != 0)
	{
		line = ft_strljoin(line, buf, read_return);
		if (line == 0)
			return (free(buf), NULL);
		read_return = read(fd, buf, BUFFER_SIZE);
		if (read_return == -1)
			return (free(line), free(buf), NULL);
		buf[read_return] = 0;
	}
	len = ft_linelen(buf);
	line = ft_strljoin(line, buf, len);
	if (line == 0 || len == read_return)
		return (free(buf), line);
	*leftovers = ft_strndup(buf + len, read_return - len + 1);
	if (!*leftovers)
		return (free(line), free(buf), NULL);
	return (free(buf), line);
}

char	*get_next_line(int fd)
{
	static char	*leftovers;
	char		*line;
	int			len;

	if (leftovers == NULL)
		return (reader(fd, NULL, &leftovers));
	len = (ft_linelen(leftovers));
	if (len > 0)
	{
		line = ft_strndup(leftovers, len);
		if (line == 0)
		{
			free(leftovers);
			leftovers = NULL;
			return (NULL);
		}
		ft_strlcpy(leftovers, leftovers + len, BUFFER_SIZE - len + 1);
		return (line);
	}
	line = ft_strndup(leftovers, ft_strlen(leftovers));
	free(leftovers);
	leftovers = NULL;
	if (line == 0)
		return (NULL);
	return (reader(fd, line, &leftovers));
}
