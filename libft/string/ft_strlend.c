/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlend.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 12:24:35 by flink             #+#    #+#             */
/*   Updated: 2026/02/19 20:38:16 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Returns the size of the string until a given Delimiter.
If Delimiter is not found it returns the length of the full string.
*/
size_t	ft_strlend(const char *str, int del)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != del)
		i++;
	return (i);
}
