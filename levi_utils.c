/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_expand_save.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 15:28:12 by flenski           #+#    #+#             */
/*   Updated: 2026/08/06 08:28:50 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*apply_function(t_data *data, size_t *i, char *cur, int s)
{
	char	*next;

	next = NULL;
	if (s == 1)
	{
		next = handle_status_code(cur, i, data->status_code);
		if (next != cur)
			free(cur);
		cur = next;
	}
	else if (s == 2)
	{
		next = mesh_tgthr(cur, NULL, *i, *i);
		if (next != cur)
			free(cur);
		cur = next;
	}
	return (next);
}

void	check_quotes(char *quote, char *cur, size_t i)
{
	if (cur[i] == '\'' && !(*quote))
		*quote = cur[i];
	else if (cur[i] == '\'')
		*quote = 0;
}
