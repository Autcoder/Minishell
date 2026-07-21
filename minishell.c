/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 22:57:31 by mprokope          #+#    #+#             */
/*   Updated: 2026/07/21 09:50:59 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main(int argc, char **argv)
{
	t_token	*tokens;
	char	*str;
	char	**env;
	t_cmd	*cmds;

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
		tokens = get_tokens(str);
		if (!tokens)
			continue ;
		// TODO: Remove once exit is implemented
		if (tokens[0].value && ft_strncmp(tokens[0].value, "exit", 4) == 0)
			break ;
		expand_tokens(tokens, env);
		handle_quotes(tokens);
		cmds = build_cmds(tokens);
		if (!cmds)
		{
			clean_up(cmds, tokens, str);
			continue ;
		}
		execute(cmds, &env);
		clean_up(cmds, tokens, str);
	}
	return (rl_clear_history(), 0);
}
