/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_expand_save.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 15:28:12 by flenski           #+#    #+#             */
/*   Updated: 2026/06/24 11:03:21 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	scan_dollar(char *str, char **key_list)
{
	size_t	i;
	size_t	j;
	size_t	l;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i == 0)
		return ((size_t)-1);
	j = 0;
	while (key_list[j])
		j++;
	l = 0;
	while (l < j)
	{
		if (!ft_strncmp(str, key_list[l], i) && ft_strlen(key_list[l]) == i)
			return (l);
		l++;
	}
	return ((size_t)-1);
}

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

static char	*mesh_tgthr(char *str, char *tmp, size_t old, size_t new)
{
	char	*ret;

	if (!tmp)
		return (ft_strnfjoin(str, &str[new], old));
	ret = malloc((old + ft_strlen(tmp) + ft_strlen(&str[new]) + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, str, old + 1);
	ft_strlcat(ret, tmp, old + ft_strlen(tmp) + 1);
	ft_strlcat(ret, &str[new], old + ft_strlen(tmp) + ft_strlen(&str[new]) + 1);
	return (ret);
}

static char	*levi_helper(char *str, size_t *idx, char **key_list, char **env)
{
	char	*expanded;
	char	*ret;
	size_t	start;
	size_t	end;

	start = *idx;
	if (!str[start + 1] || (!ft_isalnum(str[start + 1]) && str[start + 1] != '_'))
	{
		*idx = start + 1;
		return (str);
	}
	expanded = expand(&str[start + 1], key_list, env);
	if (!expanded)
	{
		// Not a valid variable name, skip this '$' for the next iteration
		*idx = start + 1;
		return (str);
	}
	end = start + 1;
	while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
		end++;
	ret = mesh_tgthr(str, expanded, start, end);
	free(expanded);
	// We don't free 'str' here anymore; we let the main levi loop handle it safely!
	return (ret);
}

char	*levi(char *str, char **env)
{
	char	**key_list;
	char	*current;
	char	*next;
	size_t	idx;

	key_list = parse_env_to_dict(env);
	if (!key_list)
		return (NULL);
	current = ft_strdup(str); // Duplicate upfront so we always own the memory
	if (!current)
		return (free_ptr_array((void **)key_list), NULL);
	idx = 0;
	while (current && current[idx])
	{
		// Find the next '$'
		if (current[idx] == '$')
		{
			next = levi_helper(current, &idx, key_list, env);
			if (next != current) // If a replacement actually happened
			{
				free(current); // Safely free the old string layer
				current = next;
			}
			if (!current)
				break ;
		}
		else
			idx++;
	}
	free_ptr_array((void **)key_list);
	return (current);
}
