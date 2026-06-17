/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:59:56 by flenski           #+#    #+#             */
/*   Updated: 2026/06/17 12:39:43 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
Returns the length of a signed number as an size_t
*/
size_t	ft_numlen(long long n)
{
	unsigned long long	x;
	size_t				len;

	if (n < 0)
		x = -(unsigned long long)n;
	else
		x = (unsigned long long)n;
	if (x == 0)
		return (1);
	len = 0;
	while (x != 0)
	{
		x /= 10;
		len++;
	}
	return (len);
}
