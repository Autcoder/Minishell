/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 02:35:02 by mprokope          #+#    #+#             */
/*   Updated: 2026/06/17 12:50:48 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"

static char	*assign(t_mylist list[FOPEN_MAX], int fd, char *line, int len)
{
	char	c;
	char	*tmp;

	c = list[fd].buffer[list[fd].i++];
	tmp = ft_realloc(line, (size_t)len, (size_t)len + 2);
	if (!tmp)
		return (free(line), NULL);
	line = tmp;
	line[len++] = c;
	line[len] = '\0';
	return (line);
}

static int	assigne_list2(int fd, t_mylist list[FOPEN_MAX])
{
	list[fd].bytes = read(list[fd].fd, list[fd].buffer, BUFFER_SIZE);
	list[fd].i = 0;
	if (list[fd].bytes <= 0)
		return (1);
	return (0);
}

static char	*get_next_line_helper(int fd, char *line, int len, int switcher)
{
	static t_mylist	list[FOPEN_MAX];

	list[fd].fd = fd;
	while (!switcher)
	{
		if (list[fd].i >= list[fd].bytes)
			switcher = assigne_list2(fd, list);
		if (list[fd].bytes < 0)
			return (free(line), NULL);
		while (!switcher && list[fd].i < list[fd].bytes)
		{
			line = assign(list, fd, line, len++);
			if (!(line))
				return (free(line), NULL);
			if (list[fd].buffer[list[fd].i - 1] == '\n')
				switcher = 1;
		}
	}
	return (line);
}

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
