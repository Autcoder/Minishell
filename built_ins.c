/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 09:14:18 by flenski           #+#    #+#             */
/*   Updated: 2026/08/23 14:21:11 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <errno.h>

int	ft_env(t_data *data)
{
	size_t	i;
	char	**env;

	env = data->env;
	if (!env || !*env)
	{
		write(1, "\n", 1);
		return (0);
	}
	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
	return (0);
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
		}
		if (count > 1)
			return (1);
		if (count == 1 && str[i] == 'n')
			i++;
		else
			return (1);
	}
	return (0);
}

int	ft_echo(char **cmd)
{
	size_t	i;
	int		print_newline;

	i = 1;
	print_newline = 1;
	while (cmd[i] && cmd[i][0] && !scan_for_nflag(cmd[i]))
	{
		print_newline = 0;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (print_newline)
		write(1, "\n", 1);
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

int	ft_cd(t_data *data, char **cmd)
{
	char	*cwd;
	char	*home;

	if (cmd[1] && cmd[2])
		return (put_error("cd", "too many arguments"), 2);
	cd_helper(&cwd, data);
	if (!cmd[1])
	{
		home = get_any(data->env, "HOME");
		if (!home)
			return (put_error("cd", "HOME not set"), 1);
		else
			cmd[1] = home;
	}
	if (chdir(cmd[1]) == -1)
		return (put_error("cd", strerror(errno)), EXIT_FAILURE);
	if (internal_export("OLDPWD=", data, cwd))
		return (1);
	cwd = getcwd(NULL, PATH_MAX);
	if (internal_export("PWD=", data, cwd))
		return (1);
	return (0);
}
