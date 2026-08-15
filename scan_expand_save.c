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

#include "libft/libft.h"
#include "minishell.h"

static char	*expand(char *str, char **key_list, char **env)
{
	size_t	i;
	size_t	pos;
	char	*var;

	pos = scan_dollar(str, key_list);
	if (pos == (size_t)-1)
		return (ft_strdup(""));
	if (env[pos] == NULL)
		return (ft_strdup(""));
	i = 0;
	while (env[pos][i] != '=')
		i++;
	var = ft_strdup(&env[pos][++i]);
	if (!var)
		return (NULL);
	return (var);
}

static char	*levi_helper(char *str, size_t *idx, char **key_list, char **env)
{
	char	*expanded;
	char	*ret;
	size_t	start;
	size_t	end;
	char	c;

	start = *idx;
	c = str[start + 1];
	if (!c || (!ft_isalnum(c) && c != '_'))
	{
		*idx = start + 1;
		return (str);
	}
	expanded = expand(&str[start + 1], key_list, env);
	if (!expanded)
	{
		*idx = start + 1;
		return (str);
	}
	end = start + 1;
	while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
		end++;
	ret = mesh_tgthr(str, expanded, start, end);
	return (yet_another_help(ret, start, expanded, idx), free(expanded), ret);
}

char	*handle_status_code(char *cur, size_t *i, int status_code)
{
	char	*status;
	char	*ret;

	status = ft_itoa(status_code);
	if (!status)
		return (NULL);
	ret = mesh_tgthr(cur, status, *i, *i + 2);
	if (ret)
		*i += ft_strlen(status);
	free(status);
	return (ret);
}

char	*levi_while(char *cur, t_data *data, char **key_list, size_t i)
{
	char	*next;
	char	quote;

	quote = 0;
	while (cur && cur[0] && cur[i] && check_quotes(&quote, cur, i))
	{
		if (cur[i] == '$')
		{
			if (cur[i + 1] && cur[i + 1] == '?' && quote != '\'')
				cur = apply_function(data, &i, cur, 1);
			else if (quote == '\'')
				cur = apply_function(data, &i, cur, 2);
			else
			{
				next = levi_helper(cur, &i, key_list, data->env);
				if (next != cur)
					free(cur);
				cur = next;
			}
		}
		i++;
	}
	return (cur);
}

char	*levi(t_data *data, char *str)
{
	char	**key_list;
	char	*cur;
	size_t	i;

	if (!str)
		return (NULL);
	key_list = parse_env_to_dict(data->env);
	cur = ft_strdup(str);
	if (!key_list || !cur)
		return (free_ptr_array((void **)key_list), free(cur), NULL);
	i = 0;
	cur = levi_while(cur, data, key_list, i);
	return (free_ptr_array((void **)key_list), cur);
}
