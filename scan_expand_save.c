/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_expand_save.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 15:28:12 by flenski           #+#    #+#             */
/*   Updated: 2026/06/22 15:28:12 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_any(char *env[], char *path)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!path)
		return (NULL);
	while (env[i])
	{
		j = 0;
		while (path[j] == env[i][j])
			j++;
		if (!path[j])
			break ;
		i++;
	}
	if (env[i])
		return ((env[i] + (ft_strlen(path) + 1)));
	return (NULL);
}

char	*ft_strnjoin(char const *s1, char const *s2, size_t size)
{
	char	*str;
	size_t	len;
	char	*ptr;
	char	*temp;

	len = ft_strlen((char *)s1) + size;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	ptr = str;
	while (*s1)
		*ptr++ = *s1++;
	temp = (char *)s2;
	while (*s2 && (size_t)(s2 - temp) < size)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (str);
}

char	*ft_strnfjoin(char const *s1, char const *s2, size_t size)
{
	char	*str;
	size_t	len;
	char	*ptr;
	char	*temp;

	len = ft_strlen((char *)s1) + size;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	ptr = str;
	temp = (char *)s1;
	while (*s1 && (size_t)(s1 - temp) < size)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (str);
}

char	**parse_env_to_dict(char **environ)
{
	size_t	i;
	size_t	len;
	char	**ret;

	if (!environ[0])
		return (NULL);
	i = 0;
	while (environ[i])
		i++;
	ret = malloc(sizeof(char *) * (i + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (environ[i])
	{
		len = (size_t)(ft_strchr(environ[i], '=') - environ[i]);
		ret[i] = ft_substr(environ[i], 0, len);
		if (!ret[i])
			return (/*TODO clean_matrix(),*/ NULL);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

size_t	scan_dollar(char *str, char **key_list)
{
	size_t	i;
	size_t	j;
	size_t	l;

	i = 0;
	while (str[i] && (str[i] != ' ' && str[i] != '"'))
		i++;
	j = 0;
	while (key_list[j])
		j++;
	l = 0;
	while (l < j)
	{
		if (!ft_strncmp(str, key_list[l], i))
			return (l);
		l++;
	}
	return ((size_t)-1);
}

char	*expand(char *str, char **key_list, char **env)
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

char	*mesh_tgthr(char *str, char *tmp, size_t old, size_t new)
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

char	*levi_helper(char *str, size_t (*i)[2], char **key_list, char **env)
{
	char	*expanded;
	char	*ret;
	size_t	old;

	while (str[(*i)[0]] && str[(*i)[0]] != '$')
		(*i)[0]++;
	if (!str[*i[0]])
		return (str);
	old = (*i)[0];
	expanded = expand(&str[++(*i)[0]], key_list, env);
	// if (!expanded)
	//	return (/*free key_list*/mesh_tgthr(str, ft_strdup(""), old, old));
	while (str[(*i)[0]] && (str[(*i)[0]] != ' ' && str[(*i)[0]] != '"'))
		(*i)[0]++;
	ret = mesh_tgthr(str, expanded, old, (*i)[0]);
	free(expanded);
	if (!ret)
		return (/*free matrix*/ NULL);
	if ((*i)[1])
		free(str);
	else
		(*i)[1] = 1;
	(*i)[0] = old;
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
			return (/*free matrix*/ NULL);
	}
	/*free matrix*/
	if (!i[1])
		tmp = ft_strdup(tmp);
	return (tmp);
}
