/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:25:14 by flenski           #+#    #+#             */
/*   Updated: 2026/02/16 16:41:41 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Outputs given string `str` to `fd`.
Returns the length of the printed string upon successful print.
In case `str` == `NULL`, it prints `(null)` and returns 6.
*/
int	ft_putstr_fd(char *str, int fd)
{
	if (!str)
		return (write(fd, "(null)", 6));
	return (write(fd, str, ft_strlen(str)));
}
