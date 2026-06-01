/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 03:36:41 by mprokope          #+#    #+#             */
/*   Updated: 2025/10/28 19:05:54 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*assign(t_mylist list[FOPEN_MAX], int fd, char *line, int len)
{
	char	c;
	char	*tmp;

	c = list[fd].buffer[list[fd].i++];
	tmp = ft_realloc(line, len, len + 2);
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

char	*get_next_line_helper(int fd, char *line, int len, int switcher)
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

static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (n--)
	{
		*d++ = *s++;
	}
	return (dest);
}

void	*ft_realloc(void *ptr, size_t old, size_t new_size)
{
	char	*temp;

	if (!new_size)
		return (free(ptr), NULL);
	temp = malloc(new_size);
	if (!temp)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(temp, ptr, old);
		free(ptr);
	}
	return (temp);
}
