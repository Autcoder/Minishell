/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 15:00:03 by flenski           #+#    #+#             */
/*   Updated: 2026/06/22 15:00:33 by flenski          ###   ########.fr       */
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

void	handle_quotes(t_token *tokens)
{
	size_t	i;
	size_t	len;
	char	*clean_value;

	i = 0;
	while (tokens[i].value)
	{
		if (tokens[i].type == TOKEN_WORD)
		{
			len = ft_strlen(tokens[i].value);
			// Check if the word is wrapped in matching single or double quotes
			// forgive me for this attrocity
			if (len >= 2 && ((tokens[i].value[0] == '"' && tokens[i].value[len
							- 1] == '"') || (tokens[i].value[0] == '\''
						&& tokens[i].value[len - 1] == '\'')))
			{
				// Extract everything except quotes (first/last character)
				clean_value = ft_substr(tokens[i].value, 1, len - 2);
				free(tokens[i].value);
				tokens[i].value = clean_value;
			}
		}
		i++;
	}
}
