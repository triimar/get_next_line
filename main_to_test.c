/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_to_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:53:36 by tmarts            #+#    #+#             */
/*   Updated: 2022/12/26 20:53:58 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd);

int	main (void)
{
	int		fd1;
	char	*str;

	fd1 = open("test", O_RDONLY);
	str = get_next_line(fd1);
	while (str)
	{
		printf("%s", str);
		free(str);
		str = get_next_line(fd1);
	}
}