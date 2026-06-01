/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:31:13 by flenski           #+#    #+#             */
/*   Updated: 2026/06/01 16:25:29 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Finds and returns the length of given string `str`
*/
size_t	ft_strlen(const char *str)
{
	char	*temp;

	temp = (char *)str;
	while (*temp)
		temp++;
	return ((size_t)(temp - str));
}
