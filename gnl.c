/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:30:07 by flink             #+#    #+#             */
/*   Updated: 2026/08/24 10:47:16 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

int	has_nl(char *stash)
{
	int	i;

	i = 0;
	while (stash && stash[i])
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*join(char *stash, char *buf)
{
	char	*new_stash;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (stash && stash[i])
		i++;
	while (buf && buf[j])
		j++;
	new_stash = malloc(i + j + 1);
	if (!new_stash)
		return (NULL);
	new_stash[i + j] = 0;
	while (j--)
		new_stash[i + j] = buf[j];
	while (i--)
		new_stash[i] = stash[i];
	free(stash);
	return (new_stash);
}

char	*extract_line(char *stash)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (stash && stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = 0;
	return (line);
}

char	*trim(char *stash)
{
	char	*new_stash;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (stash && stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i] || !stash[i + 1])
		return (free(stash), NULL);
	i++;
	while (stash[i + j])
		j++;
	new_stash = malloc(j + 1);
	if (!new_stash)
		return (free(stash), NULL);
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = 0;
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		buf[BUFFER_SIZE + 1];
	char		*line;
	int			ret;

	while (!has_nl(stash))
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret <= 0)
			break ;
		buf[ret] = 0;
		stash = join(stash, buf);
	}
	if (!stash || !*stash)
		return (NULL);
	line = extract_line(stash);
	stash = trim(stash);
	return (line);
}
