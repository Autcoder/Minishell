/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 19:01:16 by mprokope          #+#    #+#             */
/*   Updated: 2026/08/24 10:54:32 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

void	put_error(char *name, char *string)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(string, 2);
	write(2, "\n", 1);
}

void	cd_helper(char **cwd, t_data *data)
{
	*cwd = get_any(data->env, "PWD");
	if (!*cwd)
		*cwd = getcwd(NULL, PATH_MAX);
	else
		*cwd = ft_strdup(*cwd);
}

void	check_if_empty(char **cwd)
{
	if (*cwd)
		free(*cwd);
}

void	rwreadline(t_data *data)
{
	setup_signals();
	while (42)
	{
		data->str = readline("minishell> ");
		if (g_sigint)
		{
			data->status_code = 130;
			g_sigint = 0;
		}
		else if (!data->str)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		else
			data->status_code = process_input(data);
		reset_loop_data(data);
	}
}

void	rwgnl(t_data *data)
{
	while (42)
	{
		data->str = get_next_line(STDIN_FILENO);
		if (g_sigint)
		{
			data->status_code = 130;
			g_sigint = 0;
		}
		else if (!data->str || !data->str[0])
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		else
			data->status_code = process_input(data);
		reset_loop_data(data);
	}
}
