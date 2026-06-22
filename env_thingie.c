/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_thingie.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 14:41:26 by mprokope          #+#    #+#             */
/*   Updated: 2026/06/22 15:25:49 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_clean(char **env, size_t i)
{
	while (i)
		free(env[i--]);
	free(env[i]);
	free(env);
}

void	ft_env(char **env)
{
	size_t	i;

	if (!env || !*env)
	{
		write(1, "\n", 1);
		return ;
	}
	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
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
			return (ft_clean(env, i), NULL);
		i++;
	}
	env[i] = NULL;
	return (env);
}

/*
void	ft_export(char **env, t_token *token)
{
	size_t	i;

	i = 0;
	while (token[i])
		i++;
}
*/
