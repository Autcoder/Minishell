/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 09:34:29 by flenski           #+#    #+#             */
/*   Updated: 2026/08/24 17:02:35 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

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
		write(STDOUT_FILENO, "^C\n", 4);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_done = 1;
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
