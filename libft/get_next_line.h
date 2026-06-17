/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 05:02:10 by mprokope          #+#    #+#             */
/*   Updated: 2026/06/17 12:52:47 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include "libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>

typedef struct mylist
{
	int		fd;
	ssize_t	bytes;
	char	buffer[BUFFER_SIZE];
	ssize_t	i;
}			t_mylist;
#endif
