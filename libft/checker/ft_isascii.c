/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:24:18 by flenski           #+#    #+#             */
/*   Updated: 2026/02/16 13:25:26 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Checks if a character is a ASCII character, returns 1 if it is, otherwise 0.
*/
int	ft_isascii(int c)
{
	return ((unsigned)c <= 127);
}
