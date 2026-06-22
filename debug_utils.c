/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 15:02:38 by flenski           #+#    #+#             */
/*   Updated: 2026/06/22 15:24:53 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Make enum printable
*/
char	*get_type_name(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return ("PIPE");
	if (type == TOKEN_REDIRECT_IN)
		return ("REDIRECT_IN");
	if (type == TOKEN_REDIRECT_OUT)
		return ("REDIRECT_OUT");
	if (type == TOKEN_HERE_DOC)
		return ("HERE_DOC");
	if (type == TOKEN_APPEND)
		return ("APPEND");
	return ("WORD");
}

void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].value)
	{
		printf("Token [%d]: '%s' | Type: %s\n", i, tokens[i].value,
			get_type_name(tokens[i].type));
		i++;
	}
	printf("Total Tokens found: %d\n", i);
}
