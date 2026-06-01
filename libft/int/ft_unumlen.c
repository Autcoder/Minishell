/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unumlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:02:57 by flenski           #+#    #+#             */
/*   Updated: 2026/02/18 10:44:41 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

/*
Returns the length of a unsigned number as an int
*/
int	ft_unumlen(unsigned long long n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}
