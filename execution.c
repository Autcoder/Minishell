#include "minishell.h"

size_t	count_words(t_token *tokens, size_t start);

int	init_cmds(t_cmd *cmds, t_token *tokens, size_t i, size_t cmd_i)
{
	size_t	words;

	words = count_words(tokens, i);
	cmds[cmd_i].argv = malloc(sizeof(char *) * (words + 1));
	if (!cmds[cmd_i].argv)
		return (1);
	cmds[cmd_i].path = NULL;
	cmds[cmd_i].fd_in = -1;
	cmds[cmd_i].fd_out = -1;
	return (0);
}
/*Checks if path is available to execute, 0 == Gut, 1 == Bad*/
int	check_access(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (0);
	else if (access(cmd, X_OK) == -1 && errno == EACCES)
		return (1);
	else if (access(cmd, X_OK) == -1 && errno == ENOENT)
		return (2);
	return (42);
}

size_t	count_cmds(t_token *tokens)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 1;
	while (tokens[i].value)
	{
		if (tokens[i].type == TOKEN_PIPE)
			count++;
		i++;
	}
	return (count);
}

size_t	count_words(t_token *tokens, size_t start)
{
	size_t	i;
	size_t	count;

	i = start;
	count = 0;
	while (tokens[i].value && tokens[i].type != TOKEN_PIPE)
	{
		if (tokens[i].type == TOKEN_WORD)
			count++;
		i++;
	}
	return (count);
}
/*TODO Handle SIgnlas in here_doc so that it reponds on ctrl-c and idk like bash*/
int	here_doc(char *eof)
{
	int	fd[2];
	pid_t	pid;
	char	*line;
	int		status;
	
	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (close(fd[0]), close(fd[1]), -1);
	if (!pid)
	{
		close(fd[0]);
		while(42)
		{
			line = readline("> ");
			if (!line)
			{
				perror("here_doc"); //TODO Temp
				break ;
			}
			if (!ft_strncmp(line, eof, ft_strlen(eof) + 1))
			{
				free(line);
				break ;
			}
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		close(fd[1]);
		exit(0);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	return (fd[0]);
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
			/*TODO Check if open fails and trow perror;*/
			else if (tokens[i].type == TOKEN_REDIRECT_OUT)
				cmds[cmd_i].fd_out = open(tokens[++i].value, O_WRONLY
					| O_CREAT | O_TRUNC, 0644);
			else if (tokens[i].type == TOKEN_APPEND)
				cmds[cmd_i].fd_out = open(tokens[++i].value, O_WRONLY
					| O_CREAT | O_APPEND, 0644);
			else if (tokens[i].type == TOKEN_HERE_DOC)
			{
				cmds[cmd_i].fd_in = here_doc(tokens[++i].value);
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

char *find_path(char *to_find, char *path1)
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
		return (/*CleanUp path*/NULL);
	i = 0;
	while (path[i])
	{
		str = ft_strjoin(path[i++], arg);
		if (!str)
			return (/*CleanUp path*/free(arg), NULL);
		if (!check_access(str))
			return (/*CleanUp*/free(arg), str);
		else if (check_access(str) == 1)
			return (/*CleanUp*/NULL);
//		else if (check_access(str) == 2)
//			return (NULL);
		free(str);
	}
	/*clean_up*/
	return (NULL);
}

size_t	init_fd_and_count(t_cmd *cmds)
{
	size_t	i;

	i = 0;
	while (cmds[i].argv)
		i++;
	return (i);
}

//fd[2] = prev fd

void	child_process(t_cmd *cmds, pid_t *p, size_t i, char **env, int fd[3])
{
	if (!p[i])
	{
		if (fd[2] != -1)
		{
			dup2(fd[2], 0);
			close(fd[2]);
		}
		if (cmds[i + 1].argv)
		{
			dup2(fd[1], 1);
			close(fd[1]);
			close(fd[0]);
		}
		if (cmds[i].fd_in != -1)
		{
			dup2(cmds[i].fd_in, 0);
			close(cmds[i].fd_in);
		}
		if (cmds[i].fd_out != -1)
		{
			dup2(cmds[i].fd_out, 1);
			close(cmds[i].fd_out);	
		}
		if (is_builtin(cmds[i], env))
			exit(0);
		else
		{
			execve(cmds[i].path, cmds[i].argv, env);
			perror("execve");
			exit(127);//TODO temp exit code
		}
	}
	if (fd[2] != -1)
		close(fd[2]);
}

int	execute(t_cmd *cmds, char **env)
{
	size_t	i;
	int		fd[3];
	pid_t	*p;
	char	*path;

	p = malloc(sizeof(pid_t) * init_fd_and_count(cmds));
	if (!p)
		return (1);
	i = 0;
	fd[2] = -1; //TODO i can move it to count_cmds
	fd[1] = -1;
	fd[0] = -1;
	path = get_any(env, "PATH");
	if (!path)
		return (free(p), 1); //TODO temp solution
	while (cmds[i].argv)
	{
		cmds[i].path = find_path(cmds[i].argv[0], path);
		if (!cmds[i].path)
		{
			(perror(cmds[i].argv[0]), close(fd[0]), close(fd[1]));
			i++;
			continue ;
		}
		if (cmds[i + 1].argv)
			pipe(fd);
		p[i] = fork();
		child_process(cmds, p, i, env, fd);
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

int	is_builtin(t_cmd cmd, char **env)
{
	if (!ft_strncmp(cmd.argv[0], "echo", 4))
		return (ft_echo(cmd.argv), 1);
	if (!ft_strncmp(cmd.argv[0], "env", 3))
		return (ft_env(env), 2);
	if (!ft_strncmp(cmd.argv[0], "cd", 2))
		return (3);
	if (!ft_strncmp(cmd.argv[0], "export", 6))
		return (4);
	if (!ft_strncmp(cmd.argv[0], "unset", 5))
		return (5);
	if (!ft_strncmp(cmd.argv[0], "pwd", 3))
		return (ft_cwd(), 6);
	if (!ft_strncmp(cmd.argv[0], "exit", 4))
		return (7);
	return (0);
}

