/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 22:57:31 by mprokope          #+#    #+#             */
/*   Updated: 2026/06/16 15:12:20 by flenski          ###   ########.fr       */
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

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();       // Tell readline we moved to a new line
	rl_replace_line("", 0); // Clear the current buffer content
	rl_redisplay();         // Force readline to redraw the prompt
}

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

int	main(int argc, char **argv, char *env[])
{
	t_token	*tokens;
	char	*str;
	int		i;

	(void)argc;
	(void)argv;
	(void)env;
	signal(SIGINT, handle_sigint); // ctrl + c
	signal(SIGQUIT, SIG_IGN);      // ctrl + /
	while (42)
	{
		str = readline("minishell> ");
		if (!str)
			break ;
		tokens = get_tokens(str);
		if (!tokens)
			continue ;
		if (ft_strncmp(tokens[0].value, "exit", 4) == 0)
			break ; // TODO: Check if causes memory leak (str)
		print_tokens(tokens);
		// TODO: expand_tokens(tokens);
		// TODO: handle_quotes(tokens);
		// TODO: execute_tokens(tokens); <-- "exit" should be done here
		// Clean up memory
		i = 0;
		while (tokens[i].value)
			free(tokens[i++].value);
		free(tokens);
		free(str);
	}
	return (rl_clear_history(), 0);
}
