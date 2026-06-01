/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:00:48 by flenski           #+#    #+#             */
/*   Updated: 2026/02/16 15:27:36 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Compares the first `slen` bytes of `p1` and `p2` and returns the difference
between the first pair of differentiating bytes found.
*/
int	ft_memcmp(const void *p1, const void *p2, size_t slen)
{
	size_t	i;

	i = 0;
	while (i < slen)
	{
		if (((unsigned char *)p1)[i] != (((unsigned char *)p2)[i]))
			return (((unsigned char *)p1)[i] - (((unsigned char *)p2)[i]));
		i++;
	}
	return (0);
}
