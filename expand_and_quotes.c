/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 15:00:03 by flenski           #+#    #+#             */
/*   Updated: 2026/08/03 08:55:57 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int	check_unclosed_quotes(char *input)
{
	size_t	i;
	char	quote;

	if (!input || !input[0])
		return (1);
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

void	expand_tokens(t_data *data)
{
	int		i;
	char	*ret;

	i = 0;
	while (data->tokens[i].value)
	{
		if (data->tokens[i].type == TOKEN_WORD
			&& data->tokens[i].value[0] != '\'')
		{
			ret = levi(data, data->tokens[i].value);
			if (ret)
			{
				free(data->tokens[i].value);
				data->tokens[i].value = ret;
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

	clean = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!clean)
		return (NULL);
	i = 0;
	j = 0;
	in_quote = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && !in_quote)
			in_quote = str[i];
		else if (str[i] == in_quote)
			in_quote = 0;
		else
			clean[j++] = str[i];
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
