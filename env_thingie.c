/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_thingie.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 14:41:26 by mprokope          #+#    #+#             */
/*   Updated: 2026/07/30 08:28:36 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

/*
Changed a lil cause if malloc failed on env[0],
while loop would've been skipped,
it would have executed	free(env[0]),
which is unitilized garbage and kabumm
*/
void	clean_arr(char **env, size_t i)
{
	if (!env)
		return ;
	while (i > 0)
	{
		i--;
		free(env[i]);
	}
	free(env);
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
		if (!env[i])
			return (clean_arr(env, i), NULL);
		i++;
	}
	env[i] = NULL;
	return (env);
}
