/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 09:46:11 by flenski           #+#    #+#             */
/*   Updated: 2026/02/18 14:09:53 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Removes every leading and trailing character inside `set` from
string `instr`, and returns the trimmed string.
If either `instr` or `set` are empty/missing or malloc fails, `NULL`
is returned.
*/
char	*ft_strtrim(const char *instr, const char *set)
{
	size_t	start;
	size_t	end;
	char	*str;

	start = 0;
	if (!instr || !set)
		return (NULL);
	while (instr[start] && ft_strchr(set, instr[start]))
		start++;
	end = ft_strlen(instr);
	while (end > start && ft_strchr(set, instr[end - 1]))
		end--;
	str = malloc(end - start + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, instr + start, end - start + 1);
	return (str);
}
