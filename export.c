/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 13:18:16 by flenski           #+#    #+#             */
/*   Updated: 2026/08/06 08:09:28 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int	add_var(t_data *data, char *cmd)
{
	size_t	i;

	i = 0;
	while (data->env[i])
		i++;
	data->env = ft_realloc(data->env, sizeof(char *) * i, sizeof(char *) * (i
				+ 2));
	if (!data->env)
		return (1);
	data->env[i++] = ft_strdup(cmd);
	data->env[i] = NULL;
	if (!data->env[i - 1])
		return (1);
	return (0);
}

int	update_var(t_data *data, char *cmd, char *temp)
{
	size_t	old;
	size_t	i;
	size_t	key_len;

	i = 0;
	key_len = (size_t)(temp - cmd);
	old = ft_strlen(cmd) + 1;
	while (data->env[i] && ft_strncmp(data->env[i], cmd, key_len))
		i++;
	if (!data->env[i])
		return (1);
	data->env[i] = ft_realloc(data->env[i], ft_strlen(data->env[i]) + 1, old);
	if (!data->env[i])
		return (1);
	ft_strlcpy(data->env[i] + key_len, cmd + key_len, old - key_len);
	return (0);
}

int	ft_export(t_data *data, char **argv)
{
	size_t	idx;
	char	*temp;

	if (!argv[1])
		return (printf("bip boop, UB incoming..\n"), 67);
	idx = 1;
	while (argv[idx])
	{
		temp = ft_strchr(argv[idx], '=');
		if (!temp)
		{
			idx++;
			continue ;
		}
		*temp = '\0';
		if (!get_any(data->env, argv[idx]))
		{
			*temp = '=';
			if (add_var(data, argv[idx]))
				return (1);
		}
		else
		{
			*temp = '=';
			if (update_var(data, argv[idx], temp))
				return (1);
		}
		idx++;
	}
	return (0);
}
