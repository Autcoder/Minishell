/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 10:25:34 by flenski           #+#    #+#             */
/*   Updated: 2026/02/18 14:07:58 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Compares the first `num` bytes of `str1` and `str2`, and returns the difference
between the first different pair. Returns 0 if the strings are the same
or `num` is 0.
*/
int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	if (!num)
		return (0);
	while (--num && *str1 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return ((unsigned char)*str1 - (unsigned char)*str2);
}
