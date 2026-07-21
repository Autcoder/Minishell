/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 09:14:18 by flenski           #+#    #+#             */
/*   Updated: 2026/07/21 13:18:32 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
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
	int		print_newline;

	i = 1;
	print_newline = 1;
	while (cmd[i] && !scan_for_nflag(cmd[i]))
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
