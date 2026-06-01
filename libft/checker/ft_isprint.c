/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:27:13 by flenski           #+#    #+#             */
/*   Updated: 2026/02/18 10:39:03 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Checks if a character is a printable ASCII character, returns 1 if it is,
otherwise 0.
*/
int	ft_isprint(int c)
{
	return ((unsigned)(c - 32) <= 126 - 32);
}
