/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:14:47 by flenski           #+#    #+#             */
/*   Updated: 2026/02/19 20:37:16 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Appends `src` to `dest` without exceeding buffer `size`, always NUL-terminating
if size > 0.
Returns the length of the string it tried to create, aka `strlen(dest) +
strlen(src)`.
*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;
	size_t	i;

	d_len = 0;
	s_len = ft_strlen(src);
	i = 0;
	while (d_len < size && dst[d_len])
		d_len++;
	if (d_len == size)
		return (size + s_len);
	while (src[i] && d_len + i + 1 < size)
	{
		dst[d_len + i] = src[i];
		i++;
	}
	dst[d_len + i] = '\0';
	return (d_len + s_len);
}
