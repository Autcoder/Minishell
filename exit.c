/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 12:05:44 by flenski           #+#    #+#             */
/*   Updated: 2026/07/28 12:49:09 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int	is_numeric(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long long	ft_atoll_exit(char *str, long long *exit_code)
{
	long long	nb;
	int			sign;

	nb = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (nb > LLONG_MAX / 10)
			return (-1);
		if (nb == LLONG_MAX / 10 && (*str - '0') > LLONG_MAX % 10)
			return (-1);
		nb = nb * 10 + (*str - '0');
		str++;
	}
	*exit_code = nb * sign;
	if (sign == -1 && (unsigned long long)nb > (unsigned long long)LLONG_MAX
		+ 1)
		return (-1);
	return (0);
}

// TODO: Get exit code as parameter
int	ft_exit(t_cmd cmd, int *exit_code)
{
	long long	status;

	ft_putstr_fd("exit\n", 2);
	if (!cmd.argv[1])
		exit(*exit_code);
	if (!is_numeric(cmd.argv[1]) || ft_atoll_exit(cmd.argv[1], &status) == -1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd.argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (1);
	}
	if (cmd.argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		// TODO: Change exit code to 1
		return (1);
	}
	exit((unsigned char)status);
	return (0);
}
