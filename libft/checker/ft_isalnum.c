/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:29:09 by flenski           #+#    #+#             */
/*   Updated: 2026/02/18 10:38:51 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Checks if a character is a letter or a digit, and returns 1 if it is,
otherwise 0.
*/
int	ft_isalnum(int c)
{
	return ((unsigned)(c | 32) - 'a' < 26 || (unsigned)(c - '0') < 10);
}
