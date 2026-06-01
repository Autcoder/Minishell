/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 10:43:19 by flenski           #+#    #+#             */
/*   Updated: 2026/02/18 14:11:09 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
Sets an area poined to by p in memory with length `len` to 0
*/
void	ft_bzero(void *p, size_t len)
{
	ft_memset(p, '\0', len);
}
