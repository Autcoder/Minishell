/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 02:50:29 by mprokope          #+#    #+#             */
/*   Updated: 2026/08/17 02:50:32 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

int	export_helper(t_data *data, char *cmd, char *temp)
{
	*temp = '\0';
	if (!get_any(data->env, cmd))
	{
		*temp = '=';
		if (add_var(data, cmd))
			return (1);
	}
	else
	{
		*temp = '=';
		if (update_var(data, cmd, temp))
			return (1);
	}
	return (0);
}

int	check_word(char *cmd, int *status, size_t *idx)
{
	if (ft_strchr(cmd, '?') || strchr_but_num(cmd) == 1)
	{
		put_error(cmd, "not a valid identifier");
		*status = 1;
		(*idx)++;
		return (1);
	}
	return (0);
}

int	check_alpha_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	strchr_but_num(char *str)
{
	char	*temp;

	temp = ft_strchr(str, '=');
	if (!temp)
		return (2);
	*temp = '\0';
	if (ft_atoi(str) || *(temp - 1) == '0')
		return (1);
	else if (check_alpha_num(str))
		return (1);
	else
		return (*temp = '=', 0);
}
