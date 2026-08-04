/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 16:03:42 by flink             #+#    #+#             */
/*   Updated: 2026/08/03 09:36:23 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	size_t	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i].value)
	{
		free(tokens[i].value);
		i++;
	}
	if (tokens)
		free(tokens);
}

/* Frees memory allocated specifically for a single prompt iteration */
void	reset_loop_data(t_data *data)
{
	if (!data)
		return ;
	if (data->str)
	{
		free(data->str);
		data->str = NULL;
	}
	if (data->tokens)
	{
		free_tokens(data->tokens);
		data->tokens = NULL;
	}
	if (data->cmds)
	{
		free_cmds(data->cmds);
		data->cmds = NULL;
	}
}

void	free_env(char **env)
{
	size_t	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

/* Frees EVERY piece of data in the entire program before exit */
void	free_all_data(t_data *data)
{
	if (!data)
		return ;
	reset_loop_data(data);
	if (data->env)
	{
		free_env(data->env);
		data->env = NULL;
	}
	if (data->p)
	{
		free(data->p);
		data->p = NULL;
	}
	rl_clear_history();
}
