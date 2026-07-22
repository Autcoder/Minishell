/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 09:14:23 by flenski           #+#    #+#             */
/*   Updated: 2026/07/22 07:15:10 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

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
				cmds[cmd_i].fd_out = open(tokens[++i].value,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (tokens[i].type == TOKEN_APPEND)
				cmds[cmd_i].fd_out = open(tokens[++i].value,
						O_WRONLY | O_CREAT | O_APPEND, 0644);
			else if (tokens[i].type == TOKEN_HERE_DOC)
			{
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
			return (to_find);
		else if (check_access(to_find) == 1)
			return (NULL);
	}
	path = ft_split(path1, ':', 1);
	if (!path)
		return (NULL);
	arg = ft_strjoin("/", to_find);
	if (!arg)
		return (/*CleanUp path*/ NULL);
	i = 0;
	while (path[i])
	{
		str = ft_strjoin(path[i++], arg);
		if (!str)
			return (/*CleanUp path*/ free(arg), NULL);
		if (!check_access(str))
			return (/*CleanUp*/ free(arg), str);
		else if (check_access(str) == 1)
			return (/*CleanUp*/ NULL);
		//		else if (check_access(str) == 2)
		//			return (NULL);
		free(str);
	}
	/*clean_up*/
	return (NULL);
}

// TODO: Put your helpers for this into more_utils.c please.
// fd[2] = prev fd
void	child_process(t_cmd *cmds, pid_t *p, char ***env, int fd[5])
{
	if (!p[fd[4]])
	{
		if (fd[2] != -1)
		{
			dup2(fd[2], 0);
			close(fd[2]);
		}
		if (cmds[fd[4] + 1].argv)
		{
			dup2(fd[1], 1);
			close(fd[1]);
			close(fd[0]);
		}
		if (cmds[fd[4]].fd_in != -1)
		{
			dup2(cmds[fd[4]].fd_in, 0);
			close(cmds[fd[4]].fd_in);
		}
		if (cmds[fd[4]].fd_out != -1)
		{
			dup2(cmds[fd[4]].fd_out, 1);
			close(cmds[fd[4]].fd_out);
		}
		if (!fd[3])
		{
			execve(cmds[fd[4]].path, cmds[fd[4]].argv, *env);
			perror("execve");
			exit(127); // TODO: temp exit code
		}
		else
		{
			run_builtin(cmds[fd[4]], env);
			exit(0);
		}
	}
	if (fd[2] != -1)
		close(fd[2]);
}

int	execute(t_cmd *cmds, char ***env)
{
	int		i;
	int		fd[5];
	pid_t	*p;
	char	*path;

	p = malloc(sizeof(pid_t) * init_fd_and_count(cmds));
	if (!p)
		return (1);
	i = 0;
	fd[2] = -1; // TODO: i can move it to count_cmds
	fd[1] = -1;
	fd[0] = -1;
	path = get_any(*env, "PATH");
	if (!path)
		return (free(p), 1); // TODO: temp solution
	while (cmds[i].argv)
	{
		if (!cmds[1].argv && is_builtin(cmds[0]))
		{
			run_builtin(cmds[i], env);
			break ;
		}
		fd[3] = 0;
		if (is_builtin(cmds[i]))
			fd[3] = 1;
		cmds[i].path = find_path(cmds[i].argv[0], path);
		if (!fd[3] && !cmds[i].path)
		{
			(perror(cmds[i].argv[0]), close(fd[0]), close(fd[1]));
			i++;
			continue ;
		}
		if (cmds[i + 1].argv)
			pipe(fd);
		p[i] = fork();
		fd[4] = i;
		child_process(cmds, p, env, fd);
		if (cmds[i + 1].argv)
		{
			fd[2] = fd[0];
			close(fd[1]);
		}
		i++;
	}
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[2] != -1)
		close(fd[2]);
	i = 0;
	while (cmds[i].argv)
		waitpid(p[i++], NULL, 0);
	free(p);
	return (0);
}
