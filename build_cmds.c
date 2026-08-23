/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 08:46:16 by flink             #+#    #+#             */
/*   Updated: 2026/08/23 14:20:53 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
# include <errno.h>

static int	open_infile(t_cmd *cmd, char *file)
{
	if (cmd->fd_in > 2)
	{
		close(cmd->fd_in);
		cmd->fd_in = -1;
	}
	cmd->fd_in = open(file, O_RDONLY);
	if (cmd->fd_in == -1)
	{
		cmd->fd_fail = 1;
		return (put_error(file, strerror(errno)), cmd->fd_in = -2, 0);
	}
	return (0);
}

static int	open_outfile(t_cmd *cmd, char *file, int flags)
{
	if (cmd->fd_out > 2)
	{
		close(cmd->fd_out);
		cmd->fd_out = -1;
	}
	cmd->fd_out = open(file, flags, 0644);
	if (cmd->fd_out == -1)
	{
		cmd->fd_fail = 1;
		return (put_error(file, strerror(errno)), cmd->fd_out = -2, 0);
	}
	return (0);
}

static int	handle_redirect(t_cmd *cmd, t_token *tok, size_t *i, t_data *data)
{
	if (check_if_word(tok, *i) == 2)
		return (1);
	if (tok[*i].type == TOKEN_REDIRECT_IN)
		return ((*i)++, open_infile(cmd, tok[*i].value));
	if (tok[*i].type == TOKEN_REDIRECT_OUT)
		return ((*i)++, open_outfile(cmd, tok[*i].value,
				O_WRONLY | O_CREAT | O_TRUNC));
	if (tok[*i].type == TOKEN_APPEND)
		return ((*i)++, open_outfile(cmd, tok[*i].value,
				O_WRONLY | O_CREAT | O_APPEND));
	if (tok[*i].type == TOKEN_HERE_DOC)
	{
		(*i)++;
		if (cmd->fd_in > 2)
		{
			close(cmd->fd_in);
			cmd->fd_in = -1;
		}
		cmd->fd_in = here_doc(tok[*i].value, data);
		return (cmd->fd_in == -1);
	}
	return (0);
}

static int	build_one_cmd(t_data *data, t_token *tokens,
		size_t *i, size_t cmd_i)
{
	size_t	j;

	if (init_cmds(data->cmds, tokens, *i, cmd_i))
		return (1);
	j = 0;
	while (tokens[*i].value && tokens[*i].type != TOKEN_PIPE)
	{
		if (tokens[*i].type == TOKEN_WORD)
			data->cmds[cmd_i].argv[j++] = tokens[*i].value;
		else if (handle_redirect(&data->cmds[cmd_i], tokens, i, data))
			return (1);
		(*i)++;
	}
	data->cmds[cmd_i].argv[j] = NULL;
	(*i)++;
	return (0);
}

t_cmd	*build_cmds(t_token *tokens, t_data *data)
{
	size_t	i;
	size_t	cmd_i;
	size_t	n;

	i = 0;
	cmd_i = 0;
	n = count_cmds(tokens);
	if (n == SIZE_MAX)
		return (NULL);
	data->cmds = malloc(sizeof(t_cmd) * (n + 1));
	if (!data->cmds)
		return (NULL);
	ft_bzero(data->cmds, sizeof(t_cmd) * (n + 1));
	while (cmd_i < n)
	{
		if (build_one_cmd(data, tokens, &i, cmd_i))
			return (free_cmds_exec(data->cmds, cmd_i + 1), NULL);
		cmd_i++;
	}
	data->cmds[n].argv = NULL;
	return (data->cmds);
}
