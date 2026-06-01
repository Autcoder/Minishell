/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:41:46 by flenski           #+#    #+#             */
/*   Updated: 2026/02/16 16:19:49 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Finds the first occurence of `c` in the `slen` next bytes starting
at the given pointer `p` and returns a void pointer to the found occurence.
*/
void	*ft_memchr(const void *p, int c, size_t slen)
{
	while (slen--)
	{
		if (((unsigned char *)p)[slen - 1] == (unsigned char)c)
			return ((void *)((unsigned char *)p + slen - 1));
	}
	return (NULL);
}
