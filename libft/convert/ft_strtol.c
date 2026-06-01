/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:28:30 by flink             #+#    #+#             */
/*   Updated: 2026/02/18 10:44:18 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Converts a string into a long int, supports LONG_MIN till LONG_MAX
*/
long	ft_strtol(const char *str, const char *base, int blen)
{
	long	num;
	int		sign;
	int		idx;

	num = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		idx = 0;
		while (base[idx] && base[idx] != *str)
			idx++;
		if (!base[idx])
			break ;
		num = num * blen + idx;
		str++;
	}
	return (num * sign);
}
