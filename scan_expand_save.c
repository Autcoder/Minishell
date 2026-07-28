/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_expand_save.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 15:28:12 by flenski           #+#    #+#             */
/*   Updated: 2026/07/28 08:15:57 by flenski          ###   ########.fr       */
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
	return (free(expanded), ret);
}

char	*handle_status_code(char *cur, size_t i, int status_code)
{
	char	*status;
	char	*ret;

	status = ft_itoa(status_code);
	if (!status)
		return (NULL);
	ret = mesh_tgthr(cur, status, i, i + 2);
	free(status);
	return (ret);
}

char	*levi(char *str, char **env, int status_code)
{
	char	**key_list;
	char	*cur;
	char	*next;
	size_t	i;

	key_list = parse_env_to_dict(env);
	cur = ft_strdup(str);
	if (!key_list || !cur)
		return (free_ptr_array((void **)key_list), free(cur), NULL);
	i = 0;
	while (cur && cur[i])
	{
		if (cur[i] == '$')
		{
			if (cur[i + 1] && cur[i + 1] == '?')
			{
				next = handle_status_code(cur, i, status_code);
				if (next != cur)
					free(cur);
				cur = next;
				// i = 0;
			}
			else
			{
				next = levi_helper(cur, &i, key_list, env);
				if (next != cur)
					free(cur);
				cur = next;
			}
		}
		else
			i++;
	}
	return (free_ptr_array((void **)key_list), cur);
}
