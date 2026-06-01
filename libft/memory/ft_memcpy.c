/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:47:22 by flenski           #+#    #+#             */
/*   Updated: 2026/02/17 12:09:47 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Copies the first `slen` bytes from `dest` to `src`.
If `dest` and `src` or only `src` is missing, `dest` is retourned.
If only `dest` is missing, `NULL` is returned.
If `dest` and `src` overlap the behavior is undefined, if uncertain
of overlap refer to `ft_memmove`
*/
void	*ft_memcpy(void *dest, const void *src, size_t slen)
{
	size_t	i;

	if ((!dest && !src) || !src)
		return (dest);
	else if (!dest)
		return (NULL);
	i = 0;
	while (i < slen)
	{
		((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
