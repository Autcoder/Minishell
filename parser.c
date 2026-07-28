/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 03:12:20 by flenski           #+#    #+#             */
/*   Updated: 2026/07/28 11:06:06 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

static size_t	is_meta(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static void	meta_helper(char *input, size_t *i, t_token *token, char flag)
{
	if (flag == '<')
	{
		if (input[*i + 1] == '<')
		{
			token->type = TOKEN_HERE_DOC;
			token->value = ft_strdup("<<");
		}
		else
		{
			token->type = TOKEN_REDIRECT_IN;
			token->value = ft_strdup("<");
		}
		return ;
	}
	if (input[*i + 1] == '>')
	{
		token->type = TOKEN_APPEND;
		token->value = ft_strdup(">>");
	}
	else
	{
		token->type = TOKEN_REDIRECT_OUT;
		token->value = ft_strdup(">");
	}
}

/*
Handle all redirection operators and pipes
*/
static void	handle_meta(char *input, size_t *i, t_token *token)
{
	if (input[*i] == '|')
	{
		token->type = TOKEN_PIPE;
		token->value = ft_strdup("|");
	}
	else if (input[*i] == '<')
		meta_helper(input, i, token, '<');
	else if (input[*i] == '>')
		meta_helper(input, i, token, '>');
	*i += ft_strlen(token->value);
}

/*
Powers through alphanumeric characters and quotes
*/
static void	handle_word(char *input, size_t *i, t_token *token)
{
	size_t	start;
	char	quote;

	start = *i;
	quote = 0;
	token->type = TOKEN_WORD;
	while (input[*i])
	{
		if (input[*i] == '"' || input[*i] == '\'')
		{
			if (!quote)
				quote = input[*i];
			else if (quote == input[*i])
				quote = 0;
		}
		else if (!quote && (input[*i] == ' ' || is_meta(input[*i])))
			break ;
		(*i)++;
	}
	token->value = ft_substr(input, (unsigned int)start, *i - start);
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	size_t	i;
	size_t	t_idx;
	size_t	cap;

	i = 0;
	t_idx = 0;
	cap = 16;
	tokens = malloc(sizeof(t_token) * cap);
	if (!tokens)
		return (NULL);
	while (input[i])
	{
		if (input[i] == ' ' && ++i)
			continue ;
		if (t_idx >= cap - 1)
			tokens = expand_tokens_parse(tokens, &cap);
		if (is_meta(input[i]))
			handle_meta(input, &i, &tokens[t_idx++]);
		else
			handle_word(input, &i, &tokens[t_idx++]);
	}
	return (tokens[t_idx].value = NULL, tokens);
}
