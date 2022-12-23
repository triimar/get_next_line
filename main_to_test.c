/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_to_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:53:36 by tmarts            #+#    #+#             */
/*   Updated: 2022/12/23 21:48:39 by tmarts           ###   ########.fr       */
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
	int		fd2;
	char	*str2;
	int		fd3;
	char	*str3;
	
	fd1 = open("marie_under.txt", O_RDONLY);
	str = get_next_line(fd1);
	printf("The next line is: [%s]", str);
	free(str);
	str = get_next_line(fd1);
	printf("The next line is: [%s]", str);
	free(str);
	str = get_next_line(fd1);
	printf("The next line is: [%s]", str);
	free(str);
	str = get_next_line(fd1);
	printf("The next line is: [%s]", str);
	free(str);
	str = get_next_line(fd1);
	printf("The next line is: [%s]", str);
	free(str);
	str = get_next_line(fd1);
	printf("The next line is: [%s]", str);
	free(str);
	printf("_________________________________________\n");
	fd2 = open("neuromancer.txt", O_RDONLY);
	str2 = get_next_line(fd2);
	printf("The next line is: [%s]", str2);
	free(str2);
	str2 = get_next_line(fd2);
	printf("The next line is: [%s]", str2);
	free(str2);
	str2 = get_next_line(fd2);
	printf("The next line is: [%s]", str2);
	free(str2);
	printf("_________________________________________\n");
	fd3 = open("notext.txt", O_RDONLY);
	str3 = get_next_line(fd3);
	printf("The next line is: [%s]", str3);
	free(str3);
	str3 = get_next_line(fd3);
	printf("The next line is: [%s]", str3);
	free(str3);
	str3 = get_next_line(fd3);
	printf("The next line is: [%s]", str3);
	free(str3);
}