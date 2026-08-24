/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 12:05:44 by flenski           #+#    #+#             */
/*   Updated: 2026/08/24 14:53:05 by flink            ###   ########.fr       */
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

long long	ft_atoll_exit(char *str, long long *status)
{
	unsigned long long	nb;
	int					sign;
	unsigned long long	lm;

	nb = 0;
	sign = 1;
	lm = (unsigned long long)LLONG_MAX;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (nb > lm / 10 || (nb == lm / 10 && (unsigned long long)(*str
				- '0') > (lm % 10 + (sign == -1))))
			return (-1);
		nb = nb * 10 + (unsigned long long)(*str++ - '0');
	}
	if (sign == -1 && nb == lm + 1)
		*status = LLONG_MIN;
	else
		*status = (long long)nb * sign;
	return (0);
}

// NOTE: casting to unsigned char, because then reading only 8-bit values
void	exit_clean(long long exit_code, t_data *data)
{
	ft_putstr_fd("exit\n", 2);
	free_all_data(data);
	exit((unsigned char)exit_code);
}

int	ft_exit(t_data *data)
{
	long long	status;

	if (!data->cmds->argv || !data->cmds->argv[1])
		exit_clean(data->status_code, data);
	if (!is_numeric(data->cmds->argv[1]) || ft_atoll_exit(data->cmds->argv[1],
			&status) == -1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(data->cmds->argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		data->status_code = 2;
		exit_clean(data->status_code, data);
	}
	if (data->cmds->argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		data->status_code = 2;
		return (2);
	}
	exit_clean(status, data);
	return (0);
}
