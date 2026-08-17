/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levi_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 02:05:57 by mprokope          #+#    #+#             */
/*   Updated: 2026/08/17 02:06:01 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

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

char	*levi_while_here_doc(char *cur, t_data *data, char **key_list, size_t i)
{
	char	*next;

	while (cur && cur[0] && cur[i])
	{
		if (cur[i] == '$')
		{
			if (cur[i + 1] && cur[i + 1] == '?')
				cur = apply_function(data, &i, cur, 1);
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

char	*levi_here_doc(t_data *data, char *str)
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
	cur = levi_while_here_doc(cur, data, key_list, i);
	return (free_ptr_array((void **)key_list), cur);
}
