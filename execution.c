/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 09:14:23 by flenski           #+#    #+#             */
/*   Updated: 2026/07/28 12:56:56 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int	check_if_word(t_token *tokens, size_t i)
{
	if (!tokens[i + 1].value || tokens[i + 1].type != TOKEN_WORD)
	{
		ft_putstr_fd("syntax error: expected value\n", 2);
		return (1);
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
				cmds[cmd_i].fd_in = open(tokens[++i].value, O_RDONLY);
			/*TODO: Check if open fails and trow perror;*/
			else if (tokens[i].type == TOKEN_REDIRECT_OUT)
			{
				if (check_if_word(tokens, i) == 1)
					return (NULL);
				cmds[cmd_i].fd_out = open(tokens[++i].value,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
			}
			else if (tokens[i].type == TOKEN_APPEND)
			{
				if (check_if_word(tokens, i) == 1)
					return (NULL);
				cmds[cmd_i].fd_out = open(tokens[++i].value,
						O_WRONLY | O_CREAT | O_APPEND, 0644);
			}
			else if (tokens[i].type == TOKEN_HERE_DOC)
			{
				if (check_if_word(tokens, i) == 1)
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

void	child_process(t_cmd *cmds, pid_t *p, char ***env, int fd[5])
{
	if (!p[fd[4]])
	{
		if (fd[2] != -1)
			dup_and_close(fd[2], 0, -1);
		if (cmds[fd[4] + 1].argv)
			dup_and_close(fd[1], 1, fd[0]);
		if (cmds[fd[4]].fd_in != -1)
			dup_and_close(cmds[fd[4]].fd_in, 0, -1);
		if (cmds[fd[4]].fd_out != -1)
			dup_and_close(cmds[fd[4]].fd_out, 1, -1);
		if (!fd[3])
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			execve(cmds[fd[4]].path, cmds[fd[4]].argv, *env);
			perror("execve");
			exit(127); // TODO: temp exit code
		}
		else
			exit((run_builtin(cmds[fd[4]], env, fd[5]), 0));
	}
	close_fd(-1, -1, fd[2], -1);
}

int	execute(t_cmd *cmds, char ***env, int status_code)
{
	int		i;
	int		fd[6];
	pid_t	*p;
	char	*path;

	p = ft_calloc(sizeof(pid_t), init_fd_and_count(cmds, fd));
	if (!p)
		return (1);
	i = 0;
	path = get_any(*env, "PATH");
	signal(SIGINT, SIG_IGN);
	while (cmds[i].argv)
	{
		if (!cmds[1].argv && is_builtin(cmds[0]))
			return (fd[4] = run_builtin(cmds[i], env, status_code), free(p),
				fd[4]);
		fd[3] = 0;
		if (is_builtin(cmds[i]))
			fd[3] = 1;
		cmds[i].path = find_path(cmds[i].argv[0], path);
		if (!fd[3] && !cmds[i].path)
		{
			ft_putstr_fd(cmds[i].argv[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			p[i++] = -1;
			continue ;
		}
		if (cmds[i + 1].argv)
			pipe(fd);
		p[i] = fork();
		fd[4] = i;
		fd[5] = status_code;
		child_process(cmds, p, env, fd);
		if (cmds[++i].argv)
		{
			fd[2] = fd[0];
			close(fd[1]);
		}
	}
	return (fd[4] = wait_helper(cmds, p), setup_signals(), fd[4]);
}
