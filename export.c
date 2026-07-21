/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 13:18:16 by flenski           #+#    #+#             */
/*   Updated: 2026/07/21 13:23:38 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

/*
** env_var: the environment variable to compare with cmd
** cmd: the command to compare with env_var
** return: 1 if env_var matches cmd, 0 otherwise
*/
static int	key_matches(const char *env_var, const char *cmd)
{
	size_t	i;

	i = 0;
	while (env_var[i] && env_var[i] != '=' && cmd[i] && cmd[i] != '=')
	{
		if (env_var[i] != cmd[i])
			return (0);
		i++;
	}
	return ((env_var[i] == '=' || env_var[i] == '\0') && (cmd[i] == '='
			|| cmd[i] == '\0'));
}

/*
** env: the environment variable to update
** cmd: the command to update env with
** idx: the index of the environment variable to update
** return: 1 if the update failed, 0 otherwise
*/
static int	update_var(char **env, char *cmd, int idx)
{
	char	*new_str;

	new_str = ft_strdup(cmd);
	if (!new_str)
		return (1);
	free(env[idx]);
	env[idx] = new_str;
	return (0);
}

/*
** env: the environment variable to add
** cmd: the command to add to env
** return: 1 if the add failed, 0 otherwise
*/
static int	add_var(char ***env, char *cmd)
{
	size_t	i;
	char	**new_env;

	i = 0;
	while ((*env)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (1);
	i = 0;
	while ((*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = ft_strdup(cmd);
	if (!new_env[i])
		return (free(new_env), 1);
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}

/*
** env: the environment variable to update
** cmd: the command to update env with
** return: 1 if the update failed, 0 otherwise
*/
int	ft_export(char ***env, char *cmd)
{
	int	i;

	if (!cmd || !*cmd)
		return (0);
	i = 0;
	while ((*env)[i])
	{
		if (key_matches((*env)[i], cmd))
		{
			if (!ft_strchr(cmd, '='))
				return (0);
			return (update_var(*env, cmd, i));
		}
		i++;
	}
	return (add_var(env, cmd));
}
