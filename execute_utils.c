/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 08:38:05 by flink             #+#    #+#             */
/*   Updated: 2026/08/06 08:43:26 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

int	execute_init(t_data *data, char **path)
{
	data->p = ft_calloc(count_and_init_exec(data->cmds, &data->ex),
			sizeof(pid_t));
	if (!data->p)
		return (1);
	*path = get_any(data->env, "PATH");
	signal(SIGINT, SIG_IGN);
	return (0);
}

int	builtin_only(t_data *data, int idx)
{
	int	ret;

	if (!(idx == 0 && !data->cmds[1].argv && data->ex.is_builtin))
		return (-1);
	ret = run_builtin(data, idx);
	free(data->p);
	data->p = NULL;
	setup_signals();
	return (ret);
}

int	command_not_found(t_data *data, int idx)
{
	if (data->ex.is_builtin)
		return (0);
	if (data->cmds[idx].path && data->cmds[idx].argv[0])
		return (0);
	ft_putstr_fd(data->cmds[idx].argv[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	if (data->cmds[idx].fd_in != -1)
		close(data->cmds[idx].fd_in);
	if (data->cmds[idx].fd_out != -1)
		close(data->cmds[idx].fd_out);
	data->p[idx] = -1;
	return (1);
}
