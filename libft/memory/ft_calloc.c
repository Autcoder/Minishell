/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:34:18 by flenski           #+#    #+#             */
/*   Updated: 2026/02/16 15:20:46 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Allocates `num` memory of `size` size and sets it to 0 
*/
void	*ft_calloc(size_t num, size_t size)
{
	void	*p;

	if (num && size && num > SIZE_MAX / size)
		return (NULL);
	p = malloc(num * size);
	if (!p)
		return (NULL);
	ft_bzero(p, num * size);
	return (p);
}
