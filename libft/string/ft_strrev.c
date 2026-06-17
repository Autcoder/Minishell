/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:01:21 by flenski           #+#    #+#             */
/*   Updated: 2026/02/17 12:09:08 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Reverses string `str` and returns it.
Returns `NULL` if `str` is empty.
*/
char	*ft_strrev(char *str)
{
	size_t	i;
	size_t	j;
	char	temp;

	if (!str)
		return (NULL);
	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
	return (str);
}
