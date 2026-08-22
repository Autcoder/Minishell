/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 08:32:52 by flink             #+#    #+#             */
/*   Updated: 2026/08/06 08:41:10 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fork_command(t_data *data, int idx)
{
	if (data->cmds[idx + 1].argv)
		if (pipe(data->ex.pipe) == -1)
			return (put_error("pipe", strerror(errno)), 1);
	data->p[idx] = fork();
	if (data->p[idx] < 0)
		return (perror("fork"), 1);
	if (data->p[idx] == 0)
		child_process(data, idx);
	return (0);
}

static void	parent_cleanup(t_data *data, int idx)
{
	if (data->cmds[idx].fd_in > 2)
	{
		close(data->cmds[idx].fd_in);
		data->cmds[idx].fd_in = -1;
	}
	if (data->cmds[idx].fd_out > 2)
	{
		close(data->cmds[idx].fd_out);
		data->cmds[idx].fd_out = -1;
	}
	if (data->cmds[idx + 1].argv)
	{
		if (data->ex.prev_fd > 2)
			close(data->ex.prev_fd);
		data->ex.prev_fd = data->ex.pipe[0];
		close(data->ex.pipe[1]);
	}
	else if (data->ex.prev_fd > 2)
		close(data->ex.prev_fd);
	if (!data->cmds[idx + 1].argv)
		data->ex.prev_fd = -1;
}

static int	set_some_stupid_s_to_minus_two_and_incr_idx(t_data *data, int *idx)
{
	data->p[(*idx)++] = -2;
	return (1);
}

static int	execute_loop(t_data *data, char *path)
{
	int	idx;
	int	ret;

	idx = 0;
	while (data->cmds[idx].argv)
	{
		data->ex.is_builtin = is_builtin(data->cmds[idx]);
		ret = builtin_only(data, idx);
		if (ret != -1)
			return (ret);
		data->cmds[idx].path = find_path(data->cmds[idx].argv[0], path);
		if (command_not_found(data, idx))
		{
			idx++;
			continue ;
		}
		if ((!data->cmds[idx].argv[0] || !data->cmds[idx].argv[0][0])
				&& set_some_stupid_s_to_minus_two_and_incr_idx(data, &idx))
			continue ;
		if (fork_command(data, idx))
			return (pipe_fail_clean(data), 1);
		parent_cleanup(data, idx++);
	}
	return (wait_helper(data));
}

int	execute(t_data *data)
{
	char	*path;
	int		ret;

	if (execute_init(data, &path))
		return (1);
	ret = execute_loop(data, path);
	setup_signals();
	free(data->p);
	data->p = NULL;
	return (ret);
}
