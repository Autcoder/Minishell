/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 19:01:16 by mprokope          #+#    #+#             */
/*   Updated: 2026/08/13 19:01:19 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

void	put_error(char *name, char *string)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(string, 2);
	write(2, "\n", 1);
}

void	cd_helper(char **cwd, t_data *data)
{
	*cwd = get_any(data->env, "PWD");
	if (!*cwd)
		*cwd = getcwd(NULL, PATH_MAX);
	else
		*cwd = ft_strdup(*cwd);
}

void	check_if_empty(char **cwd)
{
	if (*cwd)
		free(*cwd);
}
