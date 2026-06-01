/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:02:39 by flenski           #+#    #+#             */
/*   Updated: 2026/02/18 10:43:46 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Converts an unsigned long long to a string.
Supports 0 to ULLONG_MAX.
*/
char	*ft_utoa(unsigned long long n)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(ft_unumlen(n) + 1);
	if (!str)
		return (NULL);
	if (n == 0)
		str[i++] = '0';
	while (n > 0)
	{
		str[i++] = (n % 10) + '0';
		n /= 10;
	}
	str[i] = '\0';
	return (ft_strrev(str));
}
