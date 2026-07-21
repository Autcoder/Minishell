/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 09:31:39 by flenski           #+#    #+#             */
/*   Updated: 2026/07/21 09:32:21 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
