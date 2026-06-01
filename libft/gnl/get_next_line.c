/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 02:35:02 by mprokope          #+#    #+#             */
/*   Updated: 2025/10/28 19:00:55 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*line;
	int		len;
	int		switcher;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FOPEN_MAX)
		return (NULL);
	len = 0;
	switcher = 0;
	line = NULL;
	return (get_next_line_helper(fd, line, len, switcher));
}
/*
int	main(void)
{
	int	fd = open("new.txt", O_RDONLY);
	int	fd2 = open("new2.txt", O_RDONLY);
	char	*line;
	
	//while ((line = get_next_line(fd)))
    	//{
	//	printf("%s", line);
	//	free(line);
	//}

		printf("%s", get_next_line(fd));
		printf("%s", get_next_line(fd2));
		printf("%s", get_next_line(fd2));
		printf("%s", get_next_line(fd2));
		printf("%s", get_next_line(fd2));
		printf("%s", get_next_line(fd2));
		printf("%s", get_next_line(fd2));
		printf("%s", get_next_line(fd));
		printf("%s", get_next_line(fd2));
		printf("%s", get_next_line(fd));
		printf("%s", get_next_line(fd));
	close(fd);
}
*/
/*
 *
 *
 *
static t_mylist	init_lst(int fd)
{
	static t_mylist	list;

	if (!list.fd)
	{
		list.fd = fd;
		list.bytes = 0;
		list.i = 0;
	}
	return (list);
}
int	gtl2(int fd)
{
	int	len;
	int	switcher;
	static t_mylist	list;

	switcher = 0;
	len = 0;
	if (list.fd == 0)
	{
		list.fd = fd;
		list.bytes = 0;
		list.i = 0;
	}
	while (!switcher)
	{
		if (list.i >= list.bytes)
		{
			
			list.bytes = read(list.fd, list.buffer, BUFFER_SIZE);
			list.i = 0;
			if (list.bytes <= 0)
				break ;
		}
		while (list.i < list.bytes)
		{
			if (list.buffer[list.i] == '\n')
			{
				switcher = 1;
				break ;
			}
			len++;
			list.i++;
		}
	}
		if (list.buffer[list.i++] == '\n')
			len++;
	return (len);
}

int	gtl(int fd)
{
	char buf[2];
	int	i;

	i = 0;
	while (read(fd, buf, 1) > 0 && buf[0] != '\n')
		i++;
	if (buf[0] == '\n')
		i++;
	return (i);
}
*/
