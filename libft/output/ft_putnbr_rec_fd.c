/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_rec_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 06:02:34 by flenski           #+#    #+#             */
/*   Updated: 2026/02/16 16:35:40 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Outputs given number `nbr` to `fd` with recursion.
Supports INT_MIN to INT_MAX.
*/
void	ft_putnbr_fd_rec(int nbr, int fd)
{
	char	c;

	if (nbr == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr = -nbr;
	}
	if (nbr >= 10)
		ft_putnbr_fd(nbr / 10, 0, fd);
	c = nbr % 10 + '0';
	write(fd, &c, 1);
}
