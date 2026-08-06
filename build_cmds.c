/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 08:46:16 by flink             #+#    #+#             */
/*   Updated: 2026/08/06 08:46:28 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_infile(t_cmd *cmd, char *file)
{
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	cmd->fd_in = open(file, O_RDONLY);
	if (cmd->fd_in == -1)
		return (perror(file), 1);
	return (0);
}

static int	open_outfile(t_cmd *cmd, char *file, int flags)
{
	if (cmd->fd_out != -1)
		close(cmd->fd_out);
	cmd->fd_out = open(file, flags, 0644);
	if (cmd->fd_out == -1)
		return (perror(file), 1);
	return (0);
}

static int	handle_redirect(t_cmd *cmd, t_token *tokens, size_t *i)
{
	if (check_if_word(tokens, *i) == 2)
		return (1);
	if (tokens[*i].type == TOKEN_REDIRECT_IN)
		return ((*i)++, open_infile(cmd, tokens[*i].value));
	if (tokens[*i].type == TOKEN_REDIRECT_OUT)
		return ((*i)++, open_outfile(cmd, tokens[*i].value,
				O_WRONLY | O_CREAT | O_TRUNC));
	if (tokens[*i].type == TOKEN_APPEND)
		return ((*i)++, open_outfile(cmd, tokens[*i].value,
				O_WRONLY | O_CREAT | O_APPEND));
	if (tokens[*i].type == TOKEN_HERE_DOC)
	{
		(*i)++;
		if (cmd->fd_in != -1)
			close(cmd->fd_in);
		cmd->fd_in = here_doc(tokens[*i].value);
		return (cmd->fd_in == -1);
	}
	return (0);
}

static int	build_one_cmd(t_cmd *cmds, t_token *tokens,
		size_t *i, size_t cmd_i)
{
	size_t	j;

	if (init_cmds(cmds, tokens, *i, cmd_i))
		return (1);
	j = 0;
	while (tokens[*i].value && tokens[*i].type != TOKEN_PIPE)
	{
		if (tokens[*i].type == TOKEN_WORD)
			cmds[cmd_i].argv[j++] = tokens[*i].value;
		else if (handle_redirect(&cmds[cmd_i], tokens, i))
			return (1);
		(*i)++;
	}
	cmds[cmd_i].argv[j] = NULL;
	(*i)++;
	return (0);
}

t_cmd	*build_cmds(t_token *tokens)
{
	size_t	i;
	size_t	cmd_i;
	size_t	n;
	t_cmd	*cmds;

	i = 0;
	cmd_i = 0;
	n = count_cmds(tokens);
	cmds = malloc(sizeof(t_cmd) * (n + 1));
	if (!cmds)
		return (NULL);
	while (cmd_i < n)
	{
		if (build_one_cmd(cmds, tokens, &i, cmd_i))
			return (free_cmds_exec(cmds, cmd_i + 1), NULL);
		cmd_i++;
	}
	cmds[n].argv = NULL;
	return (cmds);
}
