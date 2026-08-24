/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 22:57:31 by mprokope          #+#    #+#             */
/*   Updated: 2026/08/24 09:37:35 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	free_cmds(t_cmd *cmds)
{
	size_t	i;

	if (!cmds)
		return ;
	i = 0;
	while (cmds[i].argv)
	{
		free(cmds[i].argv);
		if (cmds[i].path)
			free(cmds[i].path);
		if (cmds[i].fd_in > 2)
		{
			close(cmds[i].fd_in);
			cmds[i].fd_in = -1;
		}
		if (cmds[i].fd_out > 2)
		{
			close(cmds[i].fd_out);
			cmds[i].fd_out = -1;
		}
		i++;
	}
	free(cmds);
}

static int	init_shell(t_data *data)
{
	char	*strupid;

	setup_signals();
	data->env = init_env();
	data->cmds = NULL;
	if (!data->env)
		return (1);
	strupid = getcwd(NULL, PATH_MAX);
	internal_export("PWD=", data, &strupid);
	strupid = shel_lvl(data->env);
	internal_export("SHLVL=", data, &strupid);
	return (0);
}

static int	check_syntax(t_token *tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type != TOKEN_WORD)
			if (check_if_word(tokens, i) == 2)
				return (2);
		i++;
	}
	return (0);
}

// TODO changed some ret values
static int	process_input(t_data *data)
{
	if (check_unclosed_quotes(data->str))
		return (reset_loop_data(data), 2);
	data->tokens = get_tokens(data->str);
	if (!data->tokens)
		return (reset_loop_data(data), 1);
	if (check_syntax(data->tokens))
		return (reset_loop_data(data), 2);
	if (expand_tokens(data))
		return (reset_loop_data(data),
			put_error("export error", "var too big"), 1);
	handle_quotes(data->tokens);
	data->cmds = build_cmds(data->tokens, data);
	if (!data->cmds)
		return (reset_loop_data(data), data->status_code);
	data->status_code = execute(data);
	reset_loop_data(data);
	return (data->status_code);
}

int	main(void)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	data.status_code = 0;
	rl_outstream = stderr;
	if (init_shell(&data))
		return (1);
	while (42)
	{
		if (isatty(STDIN_FILENO))
			data.str = readline("minishell> ");
		else
		 	data.str = readline(NULL);
		if (g_sigint)
		{
			data.status_code = 130;
			g_sigint = 0;
		}
		else if (!data.str)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		else
			data.status_code = process_input(&data);
		reset_loop_data(&data);
	}
	return (free_all_data(&data), data.status_code);
}
