/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_thingie.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 14:41:26 by mprokope          #+#    #+#             */
/*   Updated: 2026/07/21 09:56:07 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	clean_arr(char **env, size_t i)
{
	while (i)
		free(env[i--]);
	free(env[i]);
	free(env);
	env = NULL;
}

char	**init_env(void)
{
	extern char	**environ;
	char		**env;
	size_t		i;

	if (!environ || !*environ)
		return (env = ft_calloc(1, sizeof(char *)), env);
	i = 0;
	while (environ[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (environ[i])
	{
		env[i] = ft_strdup(environ[i]);
		if (!env)
			return (clean_arr(env, i), NULL);
		i++;
	}
	env[i] = NULL;
	return (env);
}
