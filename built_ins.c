/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 09:14:18 by flenski           #+#    #+#             */
/*   Updated: 2026/07/21 09:14:18 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	scan_for_nflag(char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '-')
		{
			count++;
			i++;
			continue ;
		}
		if (count > 1)
			return (1);
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_echo(char **cmd)
{
	size_t	i;
	size_t	switcher;

	i = 1;
	switcher = 1;
	if (!cmd[1])
		write(1, "\n", 1);
	else
	{
		while (cmd[i])
		{
			if (!scan_for_nflag(cmd[i]))
			{
				switcher = 0;
				i++;
				continue ;
			}
			if (cmd[i] && cmd[i + 1])
			{
				ft_putstr_fd(cmd[i], 1);
				write(1, " ", 1);
			}
			else if (cmd[i] && !cmd[i + 1])
				ft_putstr_fd(cmd[i], 1);
			i++;
		}
		if (switcher)
			write(1, "\n", 1);
	}
	return (0);
}

int	ft_cwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	ft_putstr_fd(cwd, 1);
	write(1, "\n", 1);
	free(cwd);
	return (0);
}

int	ft_export(char ***env, char *cmd)
{
	size_t	i;
	size_t	old;
	char	*temp;

	i = 0;
	if (!cmd)
		return (printf("bip boop, UB incoming..\n"), 4);
	temp = ft_strchr(cmd, '=');
	*temp = '\0';
	if (!get_any(*env, cmd))
	{
		*temp = '=';
		while ((*env)[i])
			i++;
		*env = ft_realloc(*env, sizeof(char *) * i, sizeof(char *) * (i + 2));
		if (!(*env))
			return (1);
		(*env)[i++] = ft_strdup(cmd);
		(*env)[i] = NULL;
		return (4);
	}
	while ((*env)[i] && ft_strncmp((*env)[i], cmd, ft_strlen(cmd)))
		i++;
	old = ft_strlen(cmd);
	*temp = '=';
	(*env)[i] = ft_realloc((*env)[i], ft_strlen((*env)[i]) + 1, ft_strlen(cmd)
			+ 1);
	if (!(*env)[i])
		return (1);
	ft_strlcpy((*env)[i] + old, cmd + old, ft_strlen(cmd) + 1 - old);
	return (4);
}
