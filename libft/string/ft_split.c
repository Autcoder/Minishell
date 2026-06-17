/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:56:35 by flenski           #+#    #+#             */
/*   Updated: 2026/06/17 12:30:47 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	count_skip(char const *str, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*str == c)
			in_word = 0;
		str++;
	}
	return (count);
}

static int	count_keep(char const *str, char c)
{
	int	count;

	if (!str || !*str)
		return (0);
	count = 1;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

static char	*extract(char const **str, char c, int empty_str)
{
	size_t	len;
	char	*word;

	if (!empty_str)
		while (**str == c)
			(*str)++;
	len = 0;
	while ((*str)[len] && (*str)[len] != c)
		len++;
	word = ft_substr(*str, 0, len);
	*str += len;
	if (empty_str && **str == c)
		(*str)++;
	else if (!empty_str)
		while (**str == c)
			(*str)++;
	return (word);
}

/*
Splits a given string into an array of strings, split by a set Delimiter.
If empty_str is given as 0, no empty strings will be created, and just skipped.
If empty_str is given as 1, empty strings will be created.
*/
char	**ft_split(char const *str, char del, int empty_str)
{
	char	**res;
	int		count;
	int		i;

	if (!str)
		return (NULL);
	if (empty_str)
		count = count_keep(str, del);
	else
		count = count_skip(str, del);
	res = malloc(sizeof(char *) * ((size_t)count + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < count)
	{
		res[i] = extract(&str, del, empty_str);
		if (!res[i])
			return (free_ptr_array((void **)res), NULL);
		i++;
	}
	res[i] = NULL;
	return (res);
}
