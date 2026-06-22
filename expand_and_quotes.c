/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 15:00:03 by flenski           #+#    #+#             */
/*   Updated: 2026/06/22 15:32:33 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	missfit_check(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] == ' ' || !str[i + 1]))
			return (printf("Error, $ must be followed by smth.\n"), 1);
		i++;
	}
	return (0);
}

int	check_unclosed_quotes(char *input)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			if (!quote)
				quote = input[i];
			else if (quote == input[i])
				quote = 0;
		}
		i++;
	}
	if (quote)
	{
		printf("minishell: syntax error: unclosed quote\n");
		return (1);
	}
	return (0);
}

void	expand_tokens(t_token *tokens, char **env)
{
	int		i;
	char	*ret;

	i = 0;
	while (tokens[i].value)
	{
		// dont even look inside ''
		if (tokens[i].type == TOKEN_WORD && tokens[i].value[0] != '\'')
		{
			// levi on individual token.value
			ret = levi(tokens[i].value, env);
			if (ret)
			{
				free(tokens[i].value); // Free unexpanded token word
				tokens[i].value = ret; // Assign expanded string
			}
		}
		i++;
	}
}

static char	*strip_word_quotes(char *str)
{
	char	*clean;
	size_t	i;
	size_t	j;
	char	in_quote;

	// Allocate enough space
	clean = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!clean)
		return (NULL);
	i = 0;
	j = 0;
	// 0 means unquoted, '\'' means inside single, '"' means inside double
	in_quote = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && !in_quote)
			in_quote = str[i]; // Enter quote state, don't copy the quote char
		else if (str[i] == in_quote)
			in_quote = 0; // Exit quote state, don't copy the quote char
		else
			clean[j++] = str[i]; // Copy the actual literal character
		i++;
	}
	clean[j] = '\0';
	return (clean);
}

void	handle_quotes(t_token *tokens)
{
	size_t	i;
	char	*clean_value;

	i = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == TOKEN_WORD)
		{
			clean_value = strip_word_quotes(tokens[i].value);
			free(tokens[i].value);
			tokens[i].value = clean_value;
		}
		i++;
	}
}
