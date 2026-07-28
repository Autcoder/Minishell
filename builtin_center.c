/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_center.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 09:29:31 by flenski           #+#    #+#             */
/*   Updated: 2026/07/28 08:16:09 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int	is_builtin(t_cmd cmd)
{
	if (!ft_strncmp(cmd.argv[0], "echo", 5))
		return (1);
	if (!ft_strncmp(cmd.argv[0], "env", 4))
		return (2);
	if (!ft_strncmp(cmd.argv[0], "cd", 3))
		return (3);
	if (!ft_strncmp(cmd.argv[0], "export", 7))
		return (3);
	if (!ft_strncmp(cmd.argv[0], "unset", 6))
		return (5);
	if (!ft_strncmp(cmd.argv[0], "pwd", 4))
		return (6);
	if (!ft_strncmp(cmd.argv[0], "exit", 5))
		return (7);
	return (0);
}

/*TODO make the return values meningfull*/
int	run_builtin(t_cmd cmd, char ***env)
{
	if (!ft_strncmp(cmd.argv[0], "echo", 5))
		return (ft_echo(cmd.argv), 1);
	if (!ft_strncmp(cmd.argv[0], "env", 4))
		return (ft_env(*env), 2);
	if (!ft_strncmp(cmd.argv[0], "cd", 3))
		return (ft_cd(env, cmd.argv[1]));
	if (!ft_strncmp(cmd.argv[0], "export", 7))
		return (ft_export(env, cmd.argv[1]));
	if (!ft_strncmp(cmd.argv[0], "unset", 6))
		return (5);
	if (!ft_strncmp(cmd.argv[0], "pwd", 4))
		return (ft_cwd(), 6);
	if (!ft_strncmp(cmd.argv[0], "exit", 5))
		return (7);
	return (0);
}

static void	print_eof_warning(char *eof)
{
	ft_putstr_fd("minishell: warning: here-document "
		"delimited by end-of-file (wanted '",
		2);
	ft_putstr_fd(eof, 2);
	ft_putstr_fd("')\n", 2);
}

static void	child_heredoc(int write_fd, char *eof)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	while (42)
	{
		line = readline("> ");
		if (!line)
		{
			print_eof_warning(eof);
			break ;
		}
		if (!ft_strncmp(line, eof, ft_strlen(eof) + 1))
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
	exit(0);
}

int	here_doc(char *eof)
{
	int				fd[2];
	pid_t			pid;
	int				status;
	struct termios	orig;

	if (pipe(fd) == -1)
		return (-1);
	tcgetattr(STDIN_FILENO, &orig);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (close(fd[0]), close(fd[1]), -1);
	if (!pid)
		(close(fd[0]), child_heredoc(fd[1], eof));
	close(fd[1]);
	waitpid(pid, &status, 0);
	tcsetattr(STDIN_FILENO, TCSANOW, &orig);
	setup_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (close(fd[0]), -1);
	}
	return (fd[0]);
}
