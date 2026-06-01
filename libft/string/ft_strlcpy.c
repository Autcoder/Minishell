/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:49:03 by flenski           #+#    #+#             */
/*   Updated: 2026/02/19 20:37:32 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Copies `src` to `dest`, at most `size - 1` bytes, always NUL-terminating
if size > 0.
Returns the length of the `src` string, `strlen(src)`.
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*s = src;

	if (!size)
		return (ft_strlen(src));
	while (--size && *src)
		*dst++ = *src++;
	*dst = '\0';
	return (ft_strlen(s));
}
