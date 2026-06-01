/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:10:41 by flenski           #+#    #+#             */
/*   Updated: 2025/10/16 03:12:31 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_list **lst, t_list *newNode)
{
	t_list	*last;

	if (!lst || !newNode)
		return ;
	if (*lst)
	{
		last = ft_lstlast(*lst);
		last->next = newNode;
	}
	else
		*lst = newNode;
}
