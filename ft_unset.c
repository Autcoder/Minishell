/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 08:55:09 by flink             #+#    #+#             */
/*   Updated: 2026/08/03 08:55:31 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

/*Actually done by Myron but bro forgor header kek*/

static int	search_var(char *env, char *to_find)
{
	char	*temp;

	temp = ft_strchr(env, '=');
	if (!temp)
		return (0);
	*temp = '\0';
	if (ft_strlen(env) == ft_strlen(to_find) && !ft_strncmp(env, to_find,
			ft_strlen(to_find)))
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

int	ft_unset(t_data *data, char **argv)
{
	int	i;
	int	idx;

	i = 1;
	while (argv[i])
	{
		if (!get_any(data->env, argv[i++]))
			continue ;
		idx = 0;
		--i;
		while (!search_var(data->env[idx], argv[i]))
			idx++;
		if (!data->env[idx])
		{
			i++;
			continue ;
		}
		shift_left(data, &idx);
		data->env = ft_realloc(data->env, sizeof(char *) * (size_t)(idx + 2),
				sizeof(char *) * (size_t)(idx + 1));
		if (!data->env)
			return (1);
		i++;
	}
	return (0);
}
