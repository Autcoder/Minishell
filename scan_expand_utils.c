/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_expand_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 13:45:45 by flenski           #+#    #+#             */
/*   Updated: 2026/08/03 09:22:42 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

/*
 * env - enviroment, path = to find in env
 * example:
 * path = "SHELL"
*/
char	*get_any(char *env[], char *path)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!path)
		return (NULL);
	while (env && env[i])
	{
		j = 0;
		while (path[j] == env[i][j])
			j++;
		if (!path[j] && env[i][j] == '=')
			break ;
		i++;
	}
	if (env && env[i])
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

	if (!environ || !environ[0])
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
			return (free_ptr_array((void **)ret), NULL);
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
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i == 0)
		return (SIZE_MAX);
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
