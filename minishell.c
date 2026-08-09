/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 22:57:31 by mprokope          #+#    #+#             */
/*   Updated: 2026/08/06 16:17:46 by flink            ###   ########.fr       */
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
			close(cmds[i].fd_in);
		if (cmds[i].fd_out > 2)
			close(cmds[i].fd_out);
		i++;
	}
	free(cmds);
}

static int	init_shell(t_data *data)
{
	data->env = init_env();
	data->cmds = NULL;
	if (!data->env)
		return (1);
	internal_export("PWD=", data, getcwd(NULL, PATH_MAX));
	internal_export("SHLVL=", data, shel_lvl(data->env));
	setup_signals();
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
	expand_tokens(data);
	handle_quotes(data->tokens);
	data->cmds = build_cmds(data->tokens, data);
	if (!data->cmds)
		return (reset_loop_data(data), 2);
	data->status_code = execute(data);
	reset_loop_data(data);
	return (data->status_code);
}

int	main(void)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (init_shell(&data))
		return (1);
	data.status_code = 0;
	while (42)
	{
		data.str = readline("minishell> ");
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
	free_all_data(&data);
	return (data.status_code);
}
