/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 08:51:35 by flink             #+#    #+#             */
/*   Updated: 2026/08/06 08:55:16 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_pipes(t_data *data, int idx)
{
	if (data->ex.prev_fd != -1)
		dup_and_close(&data->ex.prev_fd, STDIN_FILENO, -1);
	if (data->cmds[idx + 1].argv)
	{
		close(data->ex.pipe[0]);
		dup_and_close(&data->ex.pipe[1], STDOUT_FILENO, -1);
	}
}

static void	setup_redirections(t_cmd *cmd)
{
	if (cmd->fd_in != -1)
		dup_and_close(&cmd->fd_in, STDIN_FILENO, -1);
	if (cmd->fd_out != -1)
		dup_and_close(&cmd->fd_out, STDOUT_FILENO, -1);
}

static void	exec_builtin_child(t_data *data, int idx)
{
	int	status;

	status = run_builtin(data, idx);
	free_all_data(data);
	exit(status);
}

static void	exec_external(t_data *data, t_cmd *cmd)
{
	signal(SIGPIPE, SIG_DFL);
	execve(cmd->path, cmd->argv, data->env);
	put_error(cmd->argv[0], strerror(errno));
	free_all_data(data);
	if (errno == ENOENT)
		exit(127);
	exit(126);
}

void	child_process(t_data *data, int idx)
{
	t_cmd	cmd;

	cmd = data->cmds[idx];
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_IGN);
	if (cmd.fd_in == -2 || cmd.fd_out == -2)
	{
		if (data->ex.prev_fd > 2)
			close(data->ex.prev_fd);
		if (data->cmds[idx + 1].argv)
			close_fd(data->ex.pipe[0], data->ex.pipe[1], -1, -1);
		free_all_data(data);
		exit(1);
	}
	setup_pipes(data, idx);
	setup_redirections(&cmd);
	data->cmds[idx].fd_in = cmd.fd_in;
	data->cmds[idx].fd_out = cmd.fd_out;
	if (data->ex.is_builtin)
		exec_builtin_child(data, idx);
	exec_external(data, &cmd);
}
