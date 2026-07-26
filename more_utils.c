/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 09:33:01 by flenski           #+#    #+#             */
/*   Updated: 2026/07/21 13:28:32 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

// execution helper
size_t	init_fd_and_count(t_cmd *cmds, int fd[5])
{
	size_t	i;

	i = 0;
	while (cmds[i].argv)
		i++;
	fd[2] = -1;
	fd[1] = -1;
	fd[0] = -1;
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
	{
		free(str);
		return (NULL);
	}
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
