/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:37:56 by flenski           #+#    #+#             */
/*   Updated: 2026/02/18 10:39:24 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_base_check(const char *base)
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
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	if (i < 2)
		return (0);
	return (i);
}

static void	ft_fill_str(char *res, long num, const char *base, int blen)
{
	int	len;
	int	sign;

	sign = (num < 0);
	len = ft_base_numlen(num, blen);
	if (sign)
	{
		res[0] = '-';
		num = -num;
	}
	if (num == 0)
		res[0] = base[0];
	while (num)
	{
		res[len + sign - 1] = base[num % blen];
		num /= blen;
		len--;
	}
}

static char	*ft_long_to_str(long num, const char *base, int blen)
{
	char	*res;
	int		len;
	int		sign;

	sign = (num < 0);
	len = ft_base_numlen(num, blen);
	res = malloc(len + sign + 1);
	if (!res)
		return (NULL);
	res[len + sign] = '\0';
	ft_fill_str(res, num, base, blen);
	return (res);
}

/*
Converts a string from the input_base into the output_base
*/
char	*convert_base(const char *num_str, const char *input_base,
		const char *output_base)
{
	int		in_blen;
	int		out_blen;
	long	num;

	in_blen = ft_base_check(input_base);
	out_blen = ft_base_check(output_base);
	if (!in_blen || !out_blen)
		return (NULL);
	num = ft_strtol(num_str, input_base, in_blen);
	return (ft_long_to_str(num, output_base, out_blen));
}
