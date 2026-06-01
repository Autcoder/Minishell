/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:37:21 by flenski           #+#    #+#             */
/*   Updated: 2026/02/18 14:08:54 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Finds and returns a pointer to the first occurence of `c` in string `str`.
If `c` is not found, `NULL` is returned.
*/
char	*ft_strrchr(const char *str, int c)
{
	const char	*p;

	p = str + ft_strlen(str);
	while (p >= str)
		if (*p-- == (char)c)
			return ((char *)p + 1);
	return (NULL);
}
