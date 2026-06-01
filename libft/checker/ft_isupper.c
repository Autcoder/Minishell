/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 05:30:38 by flenski           #+#    #+#             */
/*   Updated: 2026/02/16 13:26:06 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Checks if a character is a uppercase letter, returns 1 if it is, otherwise 0.
*/
int	ft_isupper(int c)
{
	return ((unsigned)(c - 'A') < 26);
}
