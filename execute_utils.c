/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 08:38:05 by flink             #+#    #+#             */
/*   Updated: 2026/08/17 13:15:33 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

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

	ret = 0;
	if ((data->ex.is_builtin == 3 || data->ex.is_builtin == 4
			|| data->ex.is_builtin == 5 || data->ex.is_builtin == 7)
		&& !data->cmds[1].argv)
	{
		ret = run_builtin(data, idx);
		free(data->p);
		data->p = NULL;
		setup_signals();
		return (ret);
	}
	else if (!(idx == 0 && !data->cmds[1].argv && !(data->cmds[idx].fd_out < 0
				|| data->cmds[idx].fd_in < 0) && data->ex.is_builtin))
		return (-1);
	return (ret);
}

int	command_not_found(t_data *data, int idx)
{
	if (data->ex.is_builtin)
		return (0);
	if (data->cmds[idx].path && data->cmds[idx].argv[0])
		return (0);
	if (data->cmds[idx].argv[0])
		put_error(data->cmds[idx].argv[0], "command not found");
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
	data->p[idx] = -1;
	return (1);
}

static char	*find_path_while(char **path, char *arg)
{
	size_t	i;
	char	*str;

	i = 0;
	while (path[i])
	{
		str = ft_strjoin(path[i++], arg);
		if (!str)
			return (clean_split(path), free(arg), NULL);
		if (!check_access(str))
			return (clean_split(path), free(arg), str);
		else if (check_access(str) == 1)
			return (clean_split(path), free(arg), NULL);
		free(str);
	}
	clean_split(path);
	free(arg);
	return (NULL);
}

char	*find_path(char *to_find, char *path1)
{
	char	**path;
	char	*arg;

	if (!to_find || !*to_find)
		return (NULL);
	if (!path1 || ft_strchr(to_find, '/'))
	{
		if (!check_access(to_find))
			return (ft_strdup(to_find));
		else if (check_access(to_find) == 1)
			return (NULL);
	}
	else
	{
		path = ft_split(path1, ':', 1);
		if (!path)
			return (NULL);
		arg = ft_strjoin("/", to_find);
		if (!arg)
			return (clean_split(path), NULL);
		return (find_path_while(path, arg));
	}
	return (NULL);
}
