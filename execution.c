/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 09:14:23 by flenski           #+#    #+#             */
/*   Updated: 2026/07/29 17:35:52 by flenski          ###   ########.fr       */
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
			return (free(cmds), NULL);
		j = 0;
		while (tokens[i].value && tokens[i].type != TOKEN_PIPE)
		{
			if (tokens[i].type == TOKEN_WORD)
				cmds[cmd_i].argv[j++] = tokens[i].value;
			else if (tokens[i].type == TOKEN_REDIRECT_IN)
			{
				if (check_if_word(tokens, i) == 2)
					return (NULL);
				cmds[cmd_i].fd_in = open(tokens[++i].value, O_RDONLY);
				if (cmds[cmd_i].fd_in == -1)
					return (perror(tokens[i].value), NULL);
			}
			/*TODO: Check if open fails and trow perror;*/
			else if (tokens[i].type == TOKEN_REDIRECT_OUT)
			{
				if (check_if_word(tokens, i) == 2)
					return (NULL);
				cmds[cmd_i].fd_out = open(tokens[++i].value,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (cmds[cmd_i].fd_out == -1)
					return (perror(tokens[i].value), NULL);
			}
			else if (tokens[i].type == TOKEN_APPEND)
			{
				if (check_if_word(tokens, i) == 2)
					return (NULL);
				cmds[cmd_i].fd_out = open(tokens[++i].value,
						O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (cmds[cmd_i].fd_out == -1)
					return (perror(tokens[i].value), NULL);
			}
			else if (tokens[i].type == TOKEN_HERE_DOC)
			{
				if (check_if_word(tokens, i) == 2)
					return (NULL);
				cmds[cmd_i].fd_in = here_doc(tokens[++i].value);
				if (cmds[cmd_i].fd_in == -1)
				{
					// here_doc cancelled with Ctrl+C
					// TODO: Free everything allocated
					return (NULL);
				}
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
		//		else if (check_access(str) == 2)
		//			return (NULL);
		free(str);
	}
	return ((clean_split(path), free(arg)), NULL);
}

// TODO: Put your helpers for this into more_utils.c please.
// fd[2] = prev fd

void	dup_and_close(int fd1, int fd_2_cpy, int fd2)
{
	dup2(fd1, fd_2_cpy);
	close_fd(fd1, fd2, -1, -1);
}

void	child_process(t_cmd *cmds, pid_t *p, char ***env, t_exec *ex)
{
	if (!p[ex->idx])
	{
		if (ex->prev_fd != -1)
			dup_and_close(ex->prev_fd, 0, -1);
		if (cmds[ex->idx + 1].argv)
			dup_and_close(ex->pipe[1], 1, ex->pipe[0]);
		if (cmds[ex->idx].fd_in != -1)
			dup_and_close(cmds[ex->idx].fd_in, 0, -1);
		if (cmds[ex->idx].fd_out != -1)
			dup_and_close(cmds[ex->idx].fd_out, 1, -1);
		if (!ex->is_builtin)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			execve(cmds[ex->idx].path, cmds[ex->idx].argv, *env);
			perror("execve");
			exit(127); // TODO: temp exit code
		}
		else
			exit(run_builtin(cmds[ex->idx], env, ex->status_code));
	}
	close_fd(-1, -1, ex->prev_fd, -1);
}

int	execute(t_cmd *cmds, char ***env, int status_code)
{
	t_exec	ex;
	pid_t	*p;
	char	*path;
	int		ret;

	p = ft_calloc(sizeof(pid_t), init_fd_and_count(cmds, (int *)&ex));
	if (!p)
		return (1);
	ex.idx = 0;
	path = get_any(*env, "PATH");
	signal(SIGINT, SIG_IGN);
	while (cmds[ex.idx].argv)
	{
		ex.is_builtin = is_builtin(cmds[ex.idx]);
		if (!cmds[1].argv && (ex.is_builtin == 4 || ex.is_builtin == 5
				|| ex.is_builtin == 7))
		{
			ret = run_builtin(cmds[ex.idx], env, status_code);
			free(p);
			return (ret);
		}
		cmds[ex.idx].path = find_path(cmds[ex.idx].argv[0], path);
		if (!ex.is_builtin && !cmds[ex.idx].path)
		{
			ft_putstr_fd(cmds[ex.idx].argv[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			p[ex.idx++] = -1;
			continue ;
		}
		if (cmds[ex.idx + 1].argv)
			pipe(ex.pipe);
		p[ex.idx] = fork();
		ex.status_code = status_code;
		child_process(cmds, p, env, &ex);
		if (cmds[++ex.idx].argv)
		{
			ex.prev_fd = ex.pipe[0];
			close(ex.pipe[1]);
		}
	}
	ret = wait_helper(cmds, p);
	setup_signals();
	return (ret);
}
