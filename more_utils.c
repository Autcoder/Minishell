/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 09:33:01 by flenski           #+#    #+#             */
/*   Updated: 2026/07/21 09:42:26 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// execution helper
size_t	init_fd_and_count(t_cmd *cmds)
{
	size_t	i;

	i = 0;
	while (cmds[i].argv)
		i++;
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
