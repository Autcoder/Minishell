/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 17:54:03 by mprokope          #+#    #+#             */
/*   Updated: 2026/07/27 17:54:07 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

/*
 *In case that env is empty, returns 1
 *Otherwise returns SHLVL + 1
 *
 *Return is always Mallocated!
 * */
char	*shel_lvl(char **env)
{
	char	*str;

	str = get_any(env, "SHLVL");
	if (!str)
		return (ft_strdup("1"));
	else
		return (ft_itoa(ft_atoi(str) + 1));
}

/*
 * name should always be Nonmallocated.
 * value should always be mallocated, it will be freed internaly
 * in case of error function will return 1
 * */
int	internal_export(char *name, t_data *data, char *value)
{
	char	*str[3];

	if (!value)
		return (1);
	str[0] = NULL;
	str[1] = ft_strjoin(name, value);
	if (!str[1])
		return (free(value), 1);
	str[2] = NULL;
	ft_export(data, str);
	free(str[1]);
	free(value);
	return (0);
}
