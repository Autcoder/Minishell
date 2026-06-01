/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:26:44 by flenski           #+#    #+#             */
/*   Updated: 2026/02/16 16:33:04 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Outputs the given number `nbr` to `fd`.
Supports LLONG_MIN to LLONG_MAX.
*/
int	ft_putnbr_fd(long long nbr, int is_unsigned, int fd)
{
	char	*str;
	int		len;

	if (is_unsigned)
		str = ft_utoa((unsigned long long)nbr);
	else
		str = ft_itoa((long long)nbr);
	if (!str)
		return (0);
	ft_putstr_fd(str, fd);
	len = (int)ft_strlen(str);
	free(str);
	return (len);
}
