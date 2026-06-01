/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:24:25 by flenski           #+#    #+#             */
/*   Updated: 2026/02/18 14:04:57 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Joins `str1` and `str2` into a new string and returns it.
If either `str1` or `str2` are missing or malloc fails, `NULL` is returned.
*/
char	*ft_strjoin(const char *str1, const char *str2)
{
	char	*str;

	if (!str1 || !str2)
		return (NULL);
	str = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, str1, ft_strlen(str1) + 1);
	ft_strlcat(str, str2, ft_strlen(str1) + ft_strlen(str2) + 1);
	return (str);
}
