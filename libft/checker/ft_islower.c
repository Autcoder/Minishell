/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 05:30:11 by flenski           #+#    #+#             */
/*   Updated: 2026/02/16 13:25:58 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Checks if a character is a lowercase letter, returns 1 if it is, otherwise 0.
*/
int	ft_islower(int c)
{
	return ((unsigned)(c - 'a') < 26);
}
