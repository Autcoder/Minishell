/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:36:17 by flenski           #+#    #+#             */
/*   Updated: 2026/02/19 20:38:33 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Searches `len` bytes of `big` for `little`, returns a pointer to the
first occurence.
If `little` isnt found, `NULL` is returned.
If `little` is empty, `big` is returned.  
*/
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	l_len;

	l_len = ft_strlen(little);
	if (!l_len)
		return ((char *)big);
	while (*big && len >= l_len)
	{
		if (!ft_strncmp(big, little, l_len))
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
