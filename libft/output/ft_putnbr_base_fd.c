/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:48:22 by flenski           #+#    #+#             */
/*   Updated: 2026/02/16 16:38:09 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Outputs the number `num` in custom base `base` to `fd`.
Returns the length of the printed number upon successful print.
Otherwise returns 0.
*/
int	ft_putnbr_base_fd(int num, const char *base, int fd)
{
	char	*s;
	int		len;

	s = itoa_base(num, base);
	if (!s)
		return (0);
	len = ft_strlen(s);
	ft_putstr_fd(s, fd);
	free(s);
	return (len);
}
