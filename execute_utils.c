/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 08:38:05 by flink             #+#    #+#             */
/*   Updated: 2026/08/06 09:01:28 by flink            ###   ########.fr       */
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
	path = ft_split(path1, ':', 1);
	if (!path)
		return (NULL);
	arg = ft_strjoin("/", to_find);
	if (!arg)
		return (clean_split(path), NULL);
	return (find_path_while(path, arg));
}
