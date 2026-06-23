/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_expand_save.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 15:28:12 by flenski           #+#    #+#             */
/*   Updated: 2026/06/23 16:40:06 by flenski          ###   ########.fr       */
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
		return (NULL);
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

static char	*levi_helper(char *str, size_t (*i)[2], char **key_list, char **env)
{
	char	*expanded;
	char	*ret;
	size_t	old;

	while (str[(*i)[0]] && str[(*i)[0]] != '$')
		(*i)[0]++;
	if (!str[*i[0]])
		return (str);
	old = (*i)[0];
	expanded = expand(&str[(*i)[0] + 1], key_list, env);
	if (!expanded)
	{
		(*i)[0]++;
		return (str);
	}
	while (str[(*i)[0] + 1] && (ft_isalnum(str[(*i)[0] + 1]) || str[(*i)[0]
			+ 1] == '_'))
		(*i)[0]++;
	(*i)[0]++; // Move past the variable name
	ret = mesh_tgthr(str, expanded, old, (*i)[0]);
	free(expanded);
	if (!ret)
		return (NULL);
	if ((*i)[1])
		free(str);
	else
		(*i)[1] = 1;
	(*i)[0] = old; // Reset index back to where it got spliced
	return (ret);
}

char	*levi(char *str, char **env)
{
	char	**key_list;
	char	*tmp;
	size_t	i[2];

	i[0] = 0;
	tmp = str;
	i[1] = 0;
	key_list = parse_env_to_dict(env);
	if (!key_list)
		return (NULL);
	while (tmp && tmp[i[0]])
	{
		tmp = levi_helper(tmp, &i, key_list, env);
		if (!tmp)
			return (free_ptr_array((void **)key_list), NULL);
	}
	if (!i[1])
		tmp = ft_strdup(tmp);
	return (tmp);
}
