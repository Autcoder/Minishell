/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 22:57:31 by mprokope          #+#    #+#             */
/*   Updated: 2026/06/19 12:30:20 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sigint = 0;

/*
Signal handler for SIGINT
*/
void	handle_sigint(int sig)
{
	(void)sig;
	g_sigint = 1;
}

/*
Signal handler for readline
*/
int	check_readline_signal(void)
{
	if (g_sigint)
	{
		g_sigint = 0;
		write(STDOUT_FILENO, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return (0);
}

/*
Setup Signal handler
*/
static void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
	rl_event_hook = check_readline_signal;
}

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

int	main(int argc, char **argv)
{
	t_token	*tokens;
	char	*str;
	int		i;
	char 	**env;
	char	*ret;

	(void)argc;
	(void)argv;
	env = init_env();
	if (!env)
		return (1);
	setup_signals();
	while (42)
	{
		str = readline("minishell> ");
		if (!str)
			break ;
		ret = levi(str, env);
		printf("%s\n", ret);
		free(ret);
		tokens = get_tokens(str);
		if (!tokens)
			continue ;
		if (tokens[0].value && ft_strncmp(tokens[0].value, "exit", 4) == 0)
			break ; // TODO: Remove once exit is implemented
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
