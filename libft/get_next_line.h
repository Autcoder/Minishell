/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 05:02:10 by mprokope          #+#    #+#             */
/*   Updated: 2025/10/28 19:07:47 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>

char	*get_next_line(int fd);
void	*ft_realloc(void *ptr, size_t old, size_t new_size);
char	*get_next_line_helper(int fd, char *line, int len, int switcher);
void	*ft_realloc(void *ptr, size_t old, size_t new_size);

typedef struct mylist
{
	int		fd;
	int		bytes;
	char	buffer[BUFFER_SIZE];
	int		i;
}	t_mylist;
#endif
