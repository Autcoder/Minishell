/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 22:57:31 by mprokope          #+#    #+#             */
/*   Updated: 2026/07/21 13:28:16 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	free_cmds(t_cmd *cmds)
{
	size_t	i;

	if (!cmds)
		return ;
	i = 0;
	while (cmds[i].argv)
	{
		free(cmds[i].argv);
		if (cmds[i].path)
			free(cmds[i].path);
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

static int	init_shell(char ***env)
{
	*env = init_env();
	if (!*env)
		return (1);
	setup_signals();
	return (0);
}

static void	process_input(char *str, char ***env)
{
	t_token	*tokens;
	t_cmd	*cmds;

	if (check_unclosed_quotes(str))
		return (free(str));
	tokens = get_tokens(str);
	if (!tokens)
		return (free(str));
	expand_tokens(tokens, *env);
	handle_quotes(tokens);
	cmds = build_cmds(tokens);
	if (!cmds)
	{
		clean_up(cmds, tokens, str);
		return ;
	}
	execute(cmds, env);
	clean_up(cmds, tokens, str);
}

int	main(int argc, char **argv)
{
	char	*str;
	char	**env;

	(void)argc;
	(void)argv;
	if (init_shell(&env))
		return (1);
	while (42)
	{
		str = readline("minishell> ");
		if (!str)
			break ;
		if (*str)
			add_history(str);
		process_input(str, &env);
	}
	rl_clear_history();
	free_ptr_array((void **)env);
	return (0);
}
