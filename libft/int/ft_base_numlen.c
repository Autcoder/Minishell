/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_numlen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:43:42 by flink             #+#    #+#             */
/*   Updated: 2026/02/18 10:44:50 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Returns the length of a number with a given base length
*/
int	ft_base_numlen(long num, int blen)
{
	int		len;
	long	tmp;

	if (num == 0)
		len = 1;
	else
		len = 0;
	tmp = num;
	if (num < 0)
		tmp = -tmp;
	while (tmp)
	{
		tmp /= blen;
		len++;
	}
	return (len);
}
