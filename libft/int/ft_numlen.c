/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:59:56 by flenski           #+#    #+#             */
/*   Updated: 2026/02/18 10:44:26 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

/*
Returns the length of a signed number as an int
*/
int	ft_numlen(long long n)
{
	unsigned long long	x;
	int					len;

	if (n < 0)
		x = -(unsigned long long)n;
	else
		x = n;
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
