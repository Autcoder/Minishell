/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:24:03 by flenski           #+#    #+#             */
/*   Updated: 2026/02/18 14:00:14 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Iterates over every character in string `str`, and applies function `f`
If either `str` or `f` are missing, nothing is done.
*/
void	ft_striteri(char *str, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (!str || !f)
		return ;
	while (*str)
		f(i++, str++);
}
