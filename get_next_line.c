/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:11:01 by tmarts            #+#    #+#             */
/*   Updated: 2022/12/20 20:32:10 by tmarts           ###   ########.fr       */
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

char	*reader(int fd, char *line, char **leftovers)
{
	char	*buf;
	int		read_return;
	int		len;

	buf = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buf)
		return (free(line), NULL);
	read_return = read(fd, buf, BUFFER_SIZE);
	if (read_return < 0)
		return (free(line), free(buf), NULL);
	buf[read_return] = 0;
	if (read_return == 0)
	{
		if (line == NULL) 
			return(free(line), free(buf), NULL);
		else
			return (free(buf), line);
	}
	while (next_line_found(buf) == 0)
	{
		if (read_return == 0)
			return (free(buf), line);
		line = ft_strljoin(line, buf, read_return);
		if (line == 0)
			return (free(line), free(buf), NULL);
		read_return = read(fd, buf, BUFFER_SIZE);
		if (read_return < 0)
			return (free(line), free(buf), NULL);
		buf[read_return] = 0;
	}
	len = next_line_found(buf);
	line = ft_strljoin(line, buf, len);
	if (line == 0)
		return(free (line), free(buf), NULL);
	if (len == read_return)
		return (free(buf), line);
	*leftovers = ft_strndup(buf + len, (read_return - len) + 1);
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
	{
		line = reader(fd, NULL, &leftovers);
		if (line == 0)
		{
			free(leftovers);
			leftovers = NULL;
			return (NULL);
		}
		return (line);
	}
	else
	{
		len = (next_line_found(leftovers));
		if (len > 0)
		{
			line = ft_strndup(leftovers, len);
			if (line == 0)
				return (free (leftovers), NULL);
			ft_strlcpy(leftovers, leftovers + len, BUFFER_SIZE - len + 1);
		}
		if (len == 0)
		{
			line = ft_strndup(leftovers, ft_strlen(leftovers));
			if (line == 0)
			{
				free(leftovers);
				leftovers = NULL;
				return (NULL);
			}	
			free(leftovers);
			leftovers = NULL;
			line = reader(fd, line, &leftovers);
			if (line == 0)
			{
				free(leftovers);
				leftovers = NULL;
				return (NULL);
			}	
		}	
		return (line);
	}
}
