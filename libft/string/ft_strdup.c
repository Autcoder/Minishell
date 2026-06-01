/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:54:39 by flenski           #+#    #+#             */
/*   Updated: 2026/02/18 13:59:33 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Duplicates `str` into a new string, and returns a pointer to it.
In case of `malloc` failure, `NULL` is returned. 
*/
char	*ft_strdup(const char *str)
{
	char	*dup;

	dup = malloc(ft_strlen(str) + 1);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, str, ft_strlen(str) + 1);
	return (dup);
}
