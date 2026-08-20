/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_center.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 09:29:31 by flenski           #+#    #+#             */
/*   Updated: 2026/08/03 08:56:31 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int	is_builtin(t_cmd cmd)
{
	if (!cmd.argv || !cmd.argv[0])
		return (0);
	if (!ft_strncmp(cmd.argv[0], "echo", 5))
		return (1);
	if (!ft_strncmp(cmd.argv[0], "env", 4))
		return (2);
	if (!ft_strncmp(cmd.argv[0], "cd", 3))
		return (3);
	if (!ft_strncmp(cmd.argv[0], "export", 7))
		return (4);
	if (!ft_strncmp(cmd.argv[0], "unset", 6))
		return (5);
	if (!ft_strncmp(cmd.argv[0], "pwd", 4))
		return (6);
	if (!ft_strncmp(cmd.argv[0], "exit", 5))
		return (7);
	return (0);
}

/*TODO make the return values meningfull*/
int	run_builtin(t_data *data, int idx)
{
	char	**commands;

	commands = data->cmds[idx].argv;
	if (!ft_strncmp(commands[0], "echo", 5))
		return (ft_echo(commands));
	if (!ft_strncmp(commands[0], "env", 4))
		return (ft_env(data));
	if (!ft_strncmp(commands[0], "cd", 3))
		return (ft_cd(data, commands));
	if (!ft_strncmp(commands[0], "export", 7))
		return (ft_export(data, commands));
	if (!ft_strncmp(commands[0], "unset", 6))
		return (ft_unset(data, commands));
	if (!ft_strncmp(commands[0], "pwd", 4))
		return (ft_cwd());
	if (!ft_strncmp(commands[0], "exit", 5))
		return (ft_exit(data));
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

static void	child_heredoc(int write_fd, char *eof, t_data *data)
{
	char	*line;

	signal(SIGINT, handle_sigint);
	while (42)
	{
		line = readline("> ");
		if (!line)
		{
			print_eof_warning(eof);
			break ;
		}
		if (g_sigint)
			exit((free(line), close(write_fd), free_all_data(data), 130));
		if (!ft_strncmp(line, eof, ft_strlen(eof) + 1))
		{
			free(line);
			break ;
		}
		expand_here_doc(&line, data);
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	exit((close(write_fd), free_all_data(data), 0));
}

int	here_doc(char *eof, t_data *data)
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
		(close(fd[0]), child_heredoc(fd[1], eof, data));
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
