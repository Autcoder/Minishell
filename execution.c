/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 09:14:23 by flenski           #+#    #+#             */
/*   Updated: 2026/07/30 16:32:03 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int	check_if_word(t_token *tokens, size_t i)
{
	if (!tokens[i + 1].value || tokens[i + 1].type != TOKEN_WORD)
	{
		ft_putstr_fd("syntax error: expected value\n", 2);
		return (2);
	}
	return (0);
}

void	free_cmds_exec(t_cmd *cmds, size_t count)
{
	size_t	i;

	if (!cmds)
		return ;
	i = 0;
	while (i < count)
	{
		if (cmds[i].fd_in != -1)
			close(cmds[i].fd_in);
		if (cmds[i].fd_out != -1)
			close(cmds[i].fd_out);
		i++;
	}
	free(cmds);
}

t_cmd	*build_cmds(t_token *tokens)
{
	size_t	i;
	t_cmd	*cmds;
	size_t	cmd_i;
	size_t	n;
	size_t	j;

	i = 0;
	cmd_i = 0;
	n = count_cmds(tokens);
	cmds = malloc(sizeof(t_cmd) * (n + 1));
	if (!cmds)
		return (NULL);
	while (cmd_i < n)
	{
		if (init_cmds(cmds, tokens, i, cmd_i))
			return (free_cmds_exec(cmds, cmd_i), NULL);
		j = 0;
		while (tokens[i].value && tokens[i].type != TOKEN_PIPE)
		{
			if (tokens[i].type == TOKEN_WORD)
				cmds[cmd_i].argv[j++] = tokens[i].value;
			else if (tokens[i].type == TOKEN_REDIRECT_IN)
			{
				if (check_if_word(tokens, i) == 2)
					return (free_cmds_exec(cmds, cmd_i + 1), NULL);
				if (cmds[cmd_i].fd_in != -1)
					close(cmds[cmd_i].fd_in);
				cmds[cmd_i].fd_in = open(tokens[++i].value, O_RDONLY);
				if (cmds[cmd_i].fd_in == -1)
					return (perror(tokens[i].value), free_cmds_exec(cmds, cmd_i
							+ 1), NULL);
			}
			else if (tokens[i].type == TOKEN_REDIRECT_OUT)
			{
				if (check_if_word(tokens, i) == 2)
					return (free_cmds_exec(cmds, cmd_i + 1), NULL);
				if (cmds[cmd_i].fd_out != -1)
					close(cmds[cmd_i].fd_out);
				cmds[cmd_i].fd_out = open(tokens[++i].value,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (cmds[cmd_i].fd_out == -1)
					return (perror(tokens[i].value), free_cmds_exec(cmds, cmd_i
							+ 1), NULL);
			}
			else if (tokens[i].type == TOKEN_APPEND)
			{
				if (check_if_word(tokens, i) == 2)
					return (free_cmds_exec(cmds, cmd_i + 1), NULL);
				if (cmds[cmd_i].fd_out != -1)
					close(cmds[cmd_i].fd_out);
				cmds[cmd_i].fd_out = open(tokens[++i].value,
						O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (cmds[cmd_i].fd_out == -1)
					return (perror(tokens[i].value), free_cmds_exec(cmds, cmd_i
							+ 1), NULL);
			}
			else if (tokens[i].type == TOKEN_HERE_DOC)
			{
				if (check_if_word(tokens, i) == 2)
					return (free_cmds_exec(cmds, cmd_i + 1), NULL);
				if (cmds[cmd_i].fd_in != -1)
					close(cmds[cmd_i].fd_in);
				cmds[cmd_i].fd_in = here_doc(tokens[++i].value);
				if (cmds[cmd_i].fd_in == -1)
					return (free_cmds_exec(cmds, cmd_i + 1), NULL);
			}
			i++;
		}
		cmds[cmd_i].argv[j] = NULL;
		i++;
		cmd_i++;
	}
	cmds[n].argv = NULL;
	return (cmds);
}

char	*find_path(char *to_find, char *path1)
{
	size_t	i;
	char	**path;
	char	*arg;
	char	*str;

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
	return ((clean_split(path), free(arg)), NULL);
}

void	dup_and_close(int fd1, int fd_2_cpy, int fd2)
{
	dup2(fd1, fd_2_cpy);
	close_fd(fd1, fd2, -1, -1);
}

void	child_process(t_data *data, int idx)
{
	t_cmd	cmd;
	int		status;

	cmd = data->cmds[idx];
	// Reset signals for normal external binaries
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	// Ignore SIGPIPE so write() returns
	//-1 instead of crashing the child process!
	signal(SIGPIPE, SIG_IGN);
	// 1. Input pipe
	if (data->ex.prev_fd != -1)
	{
		dup2(data->ex.prev_fd, STDIN_FILENO);
		close(data->ex.prev_fd);
	}
	// 2. Output pipe
	if (data->cmds[idx + 1].argv)
	{
		close(data->ex.pipe[0]);
		dup2(data->ex.pipe[1], STDOUT_FILENO);
		close(data->ex.pipe[1]);
	}
	// 3. File redirections
	if (cmd.fd_in != -1)
	{
		dup2(cmd.fd_in, STDIN_FILENO);
		close(cmd.fd_in);
	}
	if (cmd.fd_out != -1)
	{
		dup2(cmd.fd_out, STDOUT_FILENO);
		close(cmd.fd_out);
	}
	// 4. Execution
	printf("Is_built_in: %s\n", data->ex.is_builtin ? "yes" : "no");
	if (data->ex.is_builtin)
	{
		status = run_builtin(data, idx);
		free_all_data(data);
		exit(status);
	}
	signal(SIGPIPE, SIG_DFL);
	// Restore default for external binaries like cat/grep
	execve(cmd.path, cmd.argv, data->env);
	perror("execve");
	free_all_data(data);
	exit(127);
}

int	execute(t_data *data)
{
	char	*path;
	int		ret;
	int		idx;

	data->p = ft_calloc(count_and_init_exec(data->cmds, &data->ex),
			sizeof(pid_t));
	if (!data->p)
		return (1);
	idx = 0;
	path = get_any(data->env, "PATH");
	signal(SIGINT, SIG_IGN);
	while (data->cmds[idx].argv)
	{
		data->ex.is_builtin = is_builtin(data->cmds[idx]);
		data->status_code = data->status_code;
		if (idx == 0 && !data->cmds[1].argv && data->ex.is_builtin)
		{
			ret = run_builtin(data, idx);
			return (ret);
		}
		// Assign directly to data->cmds[idx].path!
		data->cmds[idx].path = find_path(data->cmds[idx].argv[0], path);
		if (!data->ex.is_builtin && (!data->cmds[idx].path || !data->cmds[idx].argv[0]))
		{
			ft_putstr_fd(data->cmds[idx].argv[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			if (data->cmds[idx].fd_in != -1)
				close(data->cmds[idx].fd_in);
			if (data->cmds[idx].fd_out != -1)
				close(data->cmds[idx].fd_out);
			data->p[idx++] = -1;
			continue ;
		}
		if (data->cmds[idx + 1].argv)
			pipe(data->ex.pipe);
		data->p[idx] = fork();
		if (data->p[idx] < 0)
		{
			perror("fork");
			return (1);
		}
		if (data->p[idx] == 0)
			child_process(data, idx);
		if (data->cmds[idx].fd_in != -1)
			close(data->cmds[idx].fd_in);
		if (data->cmds[idx].fd_out != -1)
			close(data->cmds[idx].fd_out);
		if (data->cmds[idx + 1].argv)
		{
			if (data->ex.prev_fd != -1)
				close(data->ex.prev_fd);
			data->ex.prev_fd = data->ex.pipe[0];
			close(data->ex.pipe[1]);
		}
		else if (data->ex.prev_fd != -1)
		{
			close(data->ex.prev_fd);
			data->ex.prev_fd = -1;
		}
		idx++;
	}
	ret = wait_helper(data);
	setup_signals();
	return (ret);
}
