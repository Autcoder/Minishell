/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 22:57:31 by mprokope          #+#    #+#             */
/*   Updated: 2026/06/13 10:43:37 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Make enum printable
*/
static char	*get_type_name(t_token_type type)
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

/*
Main function
*/
int	main(int argc, char **argv, char *env[])
{
	t_token	*tokens;
	char	*str;
	int		i;

	(void)argc;
	(void)argv;
	(void)env; // voided for now cause not used
	while (42)
	{
		str = readline("minishell> ");
		if (!str) // Handle Ctrl-D
			break ;
		if (*str)
			add_history(str);
		if (ft_strncmp(str, "exit", 5) == 0)
		{
			free(str);
			break ;
		}
		// run lexer
		tokens = lexer(str);
		if (!tokens)
		{
			free(str);
			continue ;
		}
		// Print tokens, types, and flags (debug)
		i = 0;
		while (tokens[i].value)
		{
			printf("Token [%d]: '%s' | Type: %s | Flags: 0x%X\n", i,
				tokens[i].value, get_type_name(tokens[i].type), tokens[i].flag);
			i++;
		}
		printf("Total Tokens found: %d\n", i);
		// Clean up allocated memory
		i = 0;
		while (tokens[i].value)
			free(tokens[i++].value);
		free(tokens);
		free(str);
	}
	// should exist... idk why it says no grrr, fix in header.
	rl_clear_history();
	return (0);
}
