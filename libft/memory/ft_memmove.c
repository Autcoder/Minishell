/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:12:45 by flenski           #+#    #+#             */
/*   Updated: 2026/02/17 12:09:40 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Copies `len` bytes from `src` to `dest`.
If `dest` is before `src`, bytes are copied forward (start -> end).
If `dest` is after `src`, bytes are copied backward (end -> start).
Returns a pointer to `dest`.
If `dest` and `src` or only `src` is missing, `dest` is retourned.
If only `dest` is missing, `NULL` is returned.
*/
void	*ft_memmove(void *dest, const void *src, size_t slen)
{
	unsigned char		*d;
	const unsigned char	*s;

	if ((!dest && !src) || !src)
		return (dest);
	else if (!dest)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d < s)
		while (slen--)
			*d++ = *s++;
	else
	{
		d += slen;
		s += slen;
		while (slen--)
			*--d = *--s;
	}
	return (dest);
}
