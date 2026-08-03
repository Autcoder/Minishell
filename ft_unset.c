/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 08:55:09 by flink             #+#    #+#             */
/*   Updated: 2026/08/03 10:26:22 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <stddef.h>

/*Actually done by Myron but bro forgor header kek*/

static int	search_var(char *env, char *to_find)
{
	char	*temp;
	size_t	key_len;

	if (!env || !to_find)
		return (0);
	temp = ft_strchr(env, '=');
	if (!temp)
		return (0);
	key_len = (size_t)(temp - env);
	*temp = '\0';
	if (ft_strlen(to_find) == key_len && ft_strncmp(env, to_find, key_len) == 0)
		return (*temp = '=', 1);
	return (*temp = '=', 0);
}

void	shift_left(t_data *data, int *idx)
{
	free(data->env[(*idx)]);
	while (data->env[(*idx)])
	{
		data->env[(*idx)] = data->env[(*idx) + 1];
		(*idx)++;
	}
}

static int	shift_and_realloc(t_data *data, int *idx)
{
	shift_left(data, idx);
	data->env = ft_realloc(data->env, sizeof(char *) * (size_t)((*idx) + 2),
			sizeof(char *) * (size_t)((*idx) + 1));
	if (!data->env)
		return (1);
	return (0);
}

int	ft_unset(t_data *data, char **argv)
{
	int	i;
	int	idx;

	i = 1;
	while (argv[i])
	{
		if (!get_any(data->env, argv[i]))
		{
			i++;
			continue ;
		}
		idx = 0;
		while (!search_var(data->env[idx], argv[i]))
			idx++;
		if (!data->env[idx])
		{
			i++;
			continue ;
		}
		if (shift_and_realloc(data, &idx))
			return (1);
		i++;
	}
	return (0);
}
