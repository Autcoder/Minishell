/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 10:39:29 by flenski           #+#    #+#             */
/*   Updated: 2026/02/18 10:43:26 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Converts a signed long long to a string.
Supports LLONG_MIN to LLONG_MAX.
*/
char	*ft_itoa(long long n)
{
	char				*str;
	int					i;
	unsigned long long	nb;

	i = 0;
	if (n < 0)
		nb = -(unsigned long long)n;
	else
		nb = n;
	str = malloc(ft_numlen(n) + (n < 0) + 1);
	if (!str)
		return (NULL);
	if (nb == 0)
		str[i++] = '0';
	while (nb > 0)
	{
		str[i++] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		str[i++] = '-';
	str[i] = '\0';
	return (ft_strrev(str));
}
