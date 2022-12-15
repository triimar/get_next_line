/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utilis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:50:30 by tmarts            #+#    #+#             */
/*   Updated: 2022/12/14 13:42:44 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*ft_calloc_str(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

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
	return (ptr);
}
size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

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
