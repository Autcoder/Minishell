#include "minishell.h"

void	check_quote(char c, char *quote)
{
	if (c == '"' || c == '\'')
	{
		if (!*quote)
			*quote = c;
		else if (c == *quote)
			*quote = 0;
	}
}

size_t	count_words(char *str)
{
	size_t	i;
	size_t	count;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ' && !quote)
			i++;
		count++;
		while (str[i] && (str[i] != ' ' || quote))
			check_quote(str[i++], &quote);
	}
	return (count);
}

size_t	get_len(char *input, size_t start, size_t *len)
{
	size_t	i;
	size_t	size;
	char	quote;

	i = start;
	size = 0;
	quote = 0;
	while (input[i] && (input[i] != ' ' || quote))
	{
		if (!quote && (input[i] == '"' || input[i] == '\''))
			quote = input[i];
		else if (quote && input[i] == quote)
			quote = 0;
		else
			size++;
		i++;
	}
	*len = i - start;
	return (size);
}

void	set_flag(char *quote, char c, t_token *token)
{
	*quote = c;
	if (*quote == '\'')
		token->flag |= FLAG_NOEXPAND;
	else
		token->flag |= FLAG_QUOTED;
}

void	cope_stripd_word(char *input, size_t start, t_token *token, size_t len)
{
	size_t	i;
	size_t	j;
	char	quote;

	token->value = malloc(len + 1);
	// if (!token->value)
	// TODO	return (NULL);
	i = start;
	j = 0;
	quote = 0;
	token->flag = FLAG_NONE;
	while (input[i] && (input[i] != ' ' || quote))
	{
		if (!quote && (input[i] == '"' || input[i] == '\''))
			set_flag(&quote, input[i], token);
		else if (quote && input[i] == quote)
			quote = 0;
		else
			token->value[j++] = input[i];
		i++;
	}
	token->value[j] = '\0';
}

void	fill_token_arr(t_token **tokens, char *input)
{
	size_t	i;
	size_t	indx;
	size_t	len;
	size_t	size;

	i = 0;
	indx = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		len = get_len(input, i, &size);
		cope_stripd_word(input, i, &((*tokens)[indx]), len);
		// return (NULL);
		i += size;
		indx++;
	}
	(*tokens)[indx].value = NULL;
}

void	free_tokens(t_token **tokens)
{
	size_t	i;

	i = 0;
	if (*tokens)
	{
		while ((*tokens)[i].value)
			free((*tokens)[i].value);
		free(*tokens);
	}
}

size_t	initial_parse(char *input, t_token **tokens)
{
	size_t	count;

	count = count_words(input);
	*tokens = malloc(sizeof(t_token) * (count + 1));
	if (!(*tokens))
		return (0);
	fill_token_arr(tokens, input);
	return (count);
}
