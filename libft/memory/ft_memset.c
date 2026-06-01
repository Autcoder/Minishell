/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:03:41 by flenski           #+#    #+#             */
/*   Updated: 2026/02/16 16:20:41 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Sets a memory area of `slen` bytes pointed to by `p` to `c`
*/
void	*ft_memset(void *p, int c, size_t slen)
{
	while (slen--)
		((unsigned char *)p)[slen] = (unsigned char)c;
	return (p);
}
