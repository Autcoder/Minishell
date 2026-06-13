/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 10:28:02 by flenski           #+#    #+#             */
/*   Updated: 2026/06/13 10:47:21 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_meta(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/*
Handle all redirection operators and pipes
*/
static void	handle_meta(char *input, int *i, t_token *token)
{
	token->flag = FLAG_NONE;
	if (input[*i] == '|')
	{
		token->type = TOKEN_PIPE;
		token->value = ft_strdup("|");
	}
	else if (input[*i] == '<')
	{
		token->type = TOKEN_REDIRECT_IN;
		if (input[*i + 1] == '<')
			token->type = TOKEN_HERE_DOC;
		token->value = ft_strdup("<");
		if (token->type == TOKEN_HERE_DOC)
			token->value = ft_strdup("<<");
	}
	else if (input[*i] == '>')
	{
		token->type = TOKEN_REDIRECT_OUT;
		if (input[*i + 1] == '>')
			token->type = TOKEN_APPEND;
		token->value = ft_strdup(">");
		if (token->type == TOKEN_APPEND)
			token->value = ft_strdup(">>");
	}
	*i += ft_strlen(token->value);
}

/*
toggle quote state and flag NOEXPAND if single quoted
*/
static void	toggle_quote(char c, char *quote, t_token *token)
{
	if (!*quote)
	{
		*quote = c;
		if (*quote == '\'')
			token->flag |= FLAG_NOEXPAND;
		token->flag |= FLAG_QUOTED;
	}
	else if (*quote == c)
		*quote = 0;
}

/*
Powers through alphanumeric characters and quotes
*/
static void	handle_word(char *input, int *i, t_token *token)
{
	int		start;
	char	quote;

	start = *i;
	quote = 0;
	token->type = TOKEN_WORD;
	token->flag = FLAG_NONE;
	while (input[*i])
	{
		if (input[*i] == '"' || input[*i] == '\'')
			toggle_quote(input[*i], &quote, token);
		else if (!quote && (input[*i] == ' ' || is_meta(input[*i])))
			break ;
		if (input[*i] == '$')
			token->flag |= FLAG_VAR;
		(*i)++;
	}
	token->value = ft_substr(input, start, *i - start);
}

/*
Compressed Master Loop (frick norminette)
*/
t_token	*lexer(char *input)
{
	t_token	*tokens;
	int		i;
	int		t_idx;
	int		cap;

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
			tokens = ft_realloc(tokens, cap * sizeof(t_token), cap);
		if (t_idx >= cap - 1)
			cap *= 2;
		if (is_meta(input[i]))
			handle_meta(input, &i, &tokens[t_idx++]);
		else
			handle_word(input, &i, &tokens[t_idx++]);
	}
	tokens[t_idx].value = NULL;
	return (tokens);
}
