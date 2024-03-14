/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_to_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:53:36 by tmarts            #+#    #+#             */
/*   Updated: 2024/03/14 14:54:16 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd);

int	main(int argc, char *argv[])
{
	int		fd1;
	char	*str;

	if (argc != 2)
	{
		printf("Program requires one argument");
		return (1);
	}
	fd1 = open(argv[1], O_RDONLY);
	str = get_next_line(fd1);
	while (str)
	{
		printf("%s", str);
		free(str);
		str = get_next_line(fd1);
	}
}
