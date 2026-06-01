/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:37:21 by flenski           #+#    #+#             */
/*   Updated: 2026/02/18 14:10:19 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Extracts `len` characters long substring from `str`, starting at
index `start`, and returns it.
If either `str` is empty or malloc fails, `NULL` is returned.
*/
char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	copy_len;
	char	*endstr;

	if (!str)
		return (NULL);
	s_len = ft_strlen(str);
	if (start >= s_len)
		return (ft_strdup(""));
	copy_len = s_len - start;
	if (len < copy_len)
		copy_len = len;
	endstr = malloc(copy_len + 1);
	if (!endstr)
		return (NULL);
	ft_strlcpy(endstr, str + start, copy_len + 1);
	return (endstr);
}
