/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 22:57:31 by mprokope          #+#    #+#             */
/*   Updated: 2026/07/30 10:30:54 by flink            ###   ########.fr       */
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
		if (cmds[i].fd_in > 2)
			close(cmds[i].fd_in);
		if (cmds[i].fd_out > 2)
			close(cmds[i].fd_out);
		i++;
	}
	free(cmds);
}

void	clean_up(t_cmd *cmds, char *str)
{
	free_cmds(cmds);
	free(str);
}

static int	init_shell(char ***env)
{
	*env = init_env();
	if (!*env)
		return (1);
	internal_export("PWD=", env, getcwd(NULL, PATH_MAX));
	internal_export("SHLVL=", env, shel_lvl(env));
	setup_signals();
	return (0);
}

void	free_tokens(t_token *tokens)
{
	size_t	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i].value)
	{
		free(tokens[i].value);
		i++;
	}
	free(tokens);
}

static int	process_input(char *str, char ***env, int status_code)
{
	t_token	*tokens;
	t_cmd	*cmds;

	if (check_unclosed_quotes(str))
		return (free(str), 1);
	tokens = get_tokens(str);
	if (!tokens)
		return (free(str), 1);
	expand_tokens(tokens, *env, status_code);
	handle_quotes(tokens);
	cmds = build_cmds(tokens);
	if (!cmds)
	{
		clean_up(cmds, str);
		free_tokens(tokens);
		return (1);
	}
	status_code = execute(cmds, env, status_code);
	clean_up(cmds, str);
	free_tokens(tokens);
	return (status_code);
}

int	main(void)
{
	char	*str;
	char	**env;
	int		status_code;

	if (init_shell(&env))
		return (1);
	status_code = 0;
	while (42)
	{
		str = readline("minishell> ");
		if (!str)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		status_code = process_input(str, &env, status_code);
	}
	rl_clear_history();
	free_ptr_array((void **)env);
	return (0);
}
