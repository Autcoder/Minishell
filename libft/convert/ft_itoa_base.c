/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:43:41 by flenski           #+#    #+#             */
/*   Updated: 2026/02/16 13:47:50 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	base_len(const char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		j = i + 1;
		while (base[j])
			if (base[i] == base[j++])
				return (0);
		i++;
	}
	return (i);
}

/*
Prolly Itoa plus custom base idfk who needs this
*/
char	*itoa_base(int n, const char *base)
{
	char	*res;
	int		blen;
	int		len;
	long	num;

	blen = base_len(base);
	if (blen < 2)
		return (NULL);
	num = n;
	if (num < 0)
		num = -num;
	len = ft_base_numlen(num, blen) + (n < 0);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	if (n < 0)
		res[0] = '-';
	while (len-- > (n < 0))
	{
		res[len] = base[num % blen];
		num /= blen;
	}
	return (res);
}
