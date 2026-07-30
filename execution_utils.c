/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 09:31:39 by flenski           #+#    #+#             */
/*   Updated: 2026/07/30 08:13:27 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

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

/* Checks if path is available to execute, 0 == Gut, 1 == Bad */
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

int	wait_helper(t_cmd *cmds, pid_t **p)
{
	int	i;
	int	status;
	int	status_code;

	i = 0;
	status_code = 0;
	while (cmds[i].argv)
	{
		if ((*p)[i] == -1)
		{
			i++;
			status_code = 127;
			continue ;
		}
		while (waitpid((*p)[i++], &status, 0) == -1)
			if (errno != EINTR)
				break ;
		if (WIFEXITED(status))
			status_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			status_code = 128 + WTERMSIG(status);
	}
	free((*p));
	return (status_code);
}
