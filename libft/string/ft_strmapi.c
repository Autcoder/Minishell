/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 09:50:37 by flenski           #+#    #+#             */
/*   Updated: 2026/02/19 20:37:49 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Applies function `f` to every character in string `s`, saves the result in
a new string and return it.
If `s` or `f` are missing or malloc fails, `NULL` is returned.
*/
char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	char	*endstr;
	size_t	i;

	if (!str || !f)
		return (NULL);
	endstr = malloc(ft_strlen(str) + 1);
	if (!endstr)
		return (NULL);
	i = 0;
	while (str[i])
	{
		endstr[i] = f(i, str[i]);
		i++;
	}
	endstr[i] = '\0';
	return (endstr);
}
