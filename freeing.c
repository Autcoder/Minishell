/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 16:03:42 by flink             #+#    #+#             */
/*   Updated: 2026/07/30 16:06:31 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

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
	if (data->p)
	{
		free(data->p);
		data->p = NULL;
	}
}

/* Frees EVERY piece of data in the entire program before exit */
void	free_all_data(t_data *data)
{
	if (!data)
		return ;
	reset_loop_data(data);
	if (data->env)
	{
		free_ptr_array((void **)data->env);
		data->env = NULL;
	}
	rl_clear_history();
}
