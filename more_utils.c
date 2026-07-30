/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 09:33:01 by flenski           #+#    #+#             */
/*   Updated: 2026/07/30 15:48:58 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

// execution helper
size_t	count_and_init_exec(t_cmd *cmds, t_exec *ex)
{
	size_t	i;

	i = 0;
	while (cmds[i].argv)
		i++;
	ex->prev_fd = -1;
	ex->pipe[0] = -1;
	ex->pipe[1] = -1;
	return (i);
}

// parser helper
t_token	*expand_tokens_parse(t_token *tokens, size_t *cap)
{
	t_token	*new_tokens;

	new_tokens = ft_realloc(tokens, *cap * sizeof(t_token), (*cap * 2)
			* sizeof(t_token));
	*cap *= 2;
	return (new_tokens);
}

// input helper
t_token	*get_tokens(char *str)
{
	t_token	*tokens;

	if (*str)
		add_history(str);
	tokens = lexer(str);
	if (!tokens)
		return (NULL);
	return (tokens);
}

void	clean_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

//Checks fd's if they are not -1 and closes them
//just pass the fd as specified
void	close_fd(int fd0, int fd1, int fd2, int fd3)
{
	if (fd0 > 2)
		close(fd0);
	if (fd1 > 2)
		close(fd1);
	if (fd2 > 2)
		close(fd2);
	if (fd3 > 2)
		close(fd3);
}
