/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 22:57:31 by mprokope          #+#    #+#             */
/*   Updated: 2026/06/27 02:41:23 by mprokope         ###   ########.fr       */
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
	char	**env;

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
		if (check_unclosed_quotes(str))
		{
			free(str);
			continue ;
		}
		// Tokenize the raw string
		tokens = get_tokens(str);
		if (!tokens)
			continue ;
		// TODO: Remove once exit is implemented
		if (tokens[0].value && ft_strncmp(tokens[0].value, "exit", 4) == 0)
			break ;
		expand_tokens(tokens, env);
		// Print tokens to verify expansion
		handle_quotes(tokens);
		print_tokens(tokens);
		// TODO: parse_to_commands(tokens);
		// TODO: execute_commands(cmds);
		// Clean up
		i = 0;
		while (tokens[i].value)
			free(tokens[i++].value);
		free(tokens);
		free(str);
		//ft_echo((char *[]){"echo", "-nnnnnnnnnnn", "lol", "xd",NULL});
		//ft_cwd();
		//ft_env(env);
		//ft_export(&env, "VAR=lol");
		//ft_export(&env, NULL);
		//ft_env(env);
	}
	return (rl_clear_history(), 0);
}
