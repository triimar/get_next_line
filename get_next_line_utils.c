/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:50:30 by tmarts            #+#    #+#             */
/*   Updated: 2022/12/17 18:59:50 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strljoin(char *s1, char *s2, int len_s2)
{
	char	*string;
	int		s1_len;
	int		j;

	if (s1 == NULL)
		return (ft_strdup(s2));
	s1_len = ft_strlen(s1);
	string = malloc(s1_len + len_s2 + 1);
	if (!string)
		return (NULL);
	while (*s1 != 0)
		*string++ = *s1++;
	j = 0;
	while (j != len_s2)
	{
		*string++ = *s2++;
		j++;
	}	
	*string = '\0';
	free(s1 - s1_len);
	return (string - s1_len - len_s2);
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

char	*ft_strdup(const char *s1)
{
	char	*s1_cpy;
	size_t	size;

	size = ft_strlen(s1) + 1;
	s1_cpy = (char *)malloc(size);
	if (s1_cpy == 0)
		return (0);
	ft_strlcpy(s1_cpy, s1, size);
	return (s1_cpy);
}
