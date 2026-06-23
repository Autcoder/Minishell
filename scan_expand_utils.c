/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_expand_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 13:45:45 by flenski           #+#    #+#             */
/*   Updated: 2026/06/23 13:45:50 by flenski          ###   ########.fr       */
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
