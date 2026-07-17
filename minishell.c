/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 22:57:31 by mprokope          #+#    #+#             */
/*   Updated: 2026/07/15 19:13:27 by flenski          ###   ########.fr       */
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
void	setup_signals(void)
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

void	free_cmds(t_cmd *cmds)
{
	size_t	i;

	if (!cmds)
		return ;
	i = 0;
	// Loop until we hit the null-term cmd
	while (cmds[i].argv)
	{
		// Free the argument pointer array
		free(cmds[i].argv);
		// Free the path string
		if (cmds[i].path)
			free(cmds[i].path);
		// Close open file descriptors
		if (cmds[i].fd_in != -1 && cmds[i].fd_in != STDIN_FILENO)
			close(cmds[i].fd_in);
		if (cmds[i].fd_out != -1 && cmds[i].fd_out != STDOUT_FILENO)
			close(cmds[i].fd_out);
		i++;
	}
	free(cmds);
}

void	clean_up(t_cmd *cmds, t_token *tokens, char *str)
{
	size_t	i;

	i = 0;
	while (tokens[i].value)
		free(tokens[i++].value);
	free(tokens);
	free(str);
	free_cmds(cmds);
}

int	main(int argc, char **argv)
{
	t_token	*tokens;
	char	*str;
	char	**env;
	t_cmd	*cmds;
	int		i;

	(void)argc;
	(void)argv;
	env = init_env();
	if (!env)
		return (1);
	setup_signals();
	while (42)
	{
		str = readline("\033[94m\u250c\033[0m(minishell)\033[94m\n\u2514\033[92m>> \033[0m");
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
		cmds = build_cmds(tokens);
		if (!cmds)
		{
			clean_up(cmds, tokens, str);
			continue ;
		}
		// Clean up
		clean_up(cmds, tokens, str);
	}
	return (rl_clear_history(), 0);
}
