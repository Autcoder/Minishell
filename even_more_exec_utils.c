/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_more_exec_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 00:59:53 by mprokope          #+#    #+#             */
/*   Updated: 2026/08/23 00:59:57 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void	pipe_fail_clean(t_data *data)
{
	if (data->ex.prev_fd != -1)
	{
		close(data->ex.prev_fd);
		data->ex.prev_fd = -1;
	}
}

void	fake_fork(t_data *data, int *idx)
{
	data->p[*idx] = fork();
	if (!data->p[*idx])
	{
		if (data->ex.prev_fd > 2)
			close(data->ex.prev_fd);
		free_all_data(data);
		if (errno == ENOENT)
			exit(127);
		exit(126);
	}
	if (data->ex.prev_fd > 2)
		close(data->ex.prev_fd);
	data->ex.prev_fd = -1;
	(*idx)++;
}
