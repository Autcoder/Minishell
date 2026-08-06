/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 08:12:30 by flink             #+#    #+#             */
/*   Updated: 2026/08/06 08:41:54 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

void	clean_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	dup_and_close(int fd1, int fd_2_cpy, int fd2)
{
	dup2(fd1, fd_2_cpy);
	close_fd(fd1, fd2, -1, -1);
}

int	check_if_word(t_token *tokens, size_t i)
{
	if (!tokens[i + 1].value || tokens[i + 1].type != TOKEN_WORD)
	{
		ft_putstr_fd("syntax error: expected value\n", 2);
		return (2);
	}
	return (0);
}

void	clean_up(t_data *data)
{
	free_cmds(data->cmds);
	if (data->str)
		free(data->str);
}
