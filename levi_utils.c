/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_expand_save.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 15:28:12 by flenski           #+#    #+#             */
/*   Updated: 2026/08/06 08:28:50 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

char	*apply_function(t_data *data, size_t *i, char *cur, int s)
{
	char	*next;

	next = NULL;
	if (s == 1)
	{
		next = handle_status_code(cur, i, data->status_code);
		if (next != cur)
			free(cur);
		cur = next;
		*i -= 1;
	}
	else if (s == 2)
	{
		next = mesh_tgthr(cur, NULL, *i, *i);
		if (next != cur)
			free(cur);
		cur = next;
	}
	return (next);
}

int	check_quotes(char *quote, char *cur, size_t i)
{
	if (cur[i] == '"' && (*quote) == 0)
	{
		*quote = '"';
	}
	else if (*quote == '"' && cur[i] == '"')
	{
		*quote = 0;
	}
	else if (cur[i] == '\'' && (*quote) == 0)
	{
		*quote = '\'';
	}
	else if (*quote == '\'' && cur[i] == '\'')
	{
		*quote = 0;
	}
	return (1);
}

/*smth for levi*/
void	yet_another_help(char *ret, size_t s, char *exp, size_t *idx)
{
	if (ret)
		*idx = s + (ft_strlen(exp) - 1);
}

int	expand_levi(t_data *data, char **ret, int i)
{
	*ret = levi(data, data->tokens[i].value);
	if (*ret)
	{
		if (ft_strlen(*ret) > 42000)
			return (free(*ret), 1);
		free(data->tokens[i].value);
		data->tokens[i].value = *ret;
	}
	return (0);
}

void	expand_here_doc(char **line, t_data *data)
{
	char	*expand;

	expand = levi_here_doc(data, *line);
	free(*line);
	if (expand)
		*line = expand;
	else
		*line = ft_strdup("");
}
