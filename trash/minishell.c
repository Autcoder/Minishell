/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 22:57:31 by mprokope          #+#    #+#             */
/*   Updated: 2026/05/31 01:39:34 by mprokope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_any(char *env[], char *path)
{
        int     i;
        int     j;

        i = 0;
		if (!path)
			return(NULL);
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
        	return ((env[i] + (strlen(path) + 1)));
		return (NULL);
}

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
		return (42);
	return (0);
}

int	ft_strlen(const char *str)
{
	char	*temp;

	temp = (char *)str;
	while (*str)
		str++;
	return ((int)(str - temp));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len;
	char	*ptr;

	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	ptr = str;
	while (*s1)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (str);
}

char	*ft_strnjoin(char const *s1, char const *s2, int size)
{
	char	*str;
	int		len;
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
	while (*s2 && s2 - temp < size)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (str);
}

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i])
		i++;
	dest = malloc(sizeof(char) * i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(src);
	if (size == 0)
		return (j);
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (j);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != (unsigned char)c && *s)
		s++;
	if (*s == '\0' && (unsigned char)c != '\0')
		return (NULL);
	return ((char *)s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;
	size_t	length_of_s;

	length_of_s = ft_strlen(s);
	if (length_of_s < start)
	{
		sub = malloc(1);
		if (!sub)
			return (NULL);
		return (sub[0] = '\0', sub);
	}
	if ((start + len) > length_of_s)
		len = length_of_s - start;
	sub = malloc(sizeof(char) * len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	return (sub[i] = '\0', sub);
}

char	**parse_env_to_dict()
{
	extern char	**environ;
	size_t		i;
	size_t		len;
	char		*tmp;
	char		**ret;

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
		len = ft_strchr(environ[i], '=') - environ[i];
		ret[i] = ft_substr(environ[i], 0, len);
		if (!ret[i])
			return (/*TODO clean_matrix(),*/NULL);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

char    *scan_expand(char *str)
{
    extern char **environ;
    char    **key_list;
    char    *temp;
    char    *ret;
    char    *var_end;
    char    *var_value;
    char    *old_ret;
	size_t	var_size;

    key_list = parse_env_to_dict();
    if (!key_list)
        return (NULL);
    ret = ft_strdup("");
    if (!ret)
        return (NULL);
    while (*str)
    {
        temp = ft_strchr(str, '$');
        if (!temp)
        {
            old_ret = ret;
            ret = ft_strjoin(ret, str);
            free(old_ret);
            break ;
        }
        old_ret = ret;
        ret = ft_strnjoin(ret, str, temp - str);
        free(old_ret);
        temp++;
        var_end = temp;
        while (*var_end && (ft_isalnum(*var_end) || *var_end == '_'))
            var_end++;
		var_size = var_end - temp;
        var_value = get_any(environ, ft_substr(temp, 0, (var_size)));
        if (var_value)
        {
            old_ret = ret;
            ret = ft_strjoin(ret, var_value);
            free(old_ret);
        }
        str = var_end;
    }
    return (ret);
}//TODO fix this shit

int	main(int argc, char **argv, char *env[])
{
	char	*str;
	char	*test;
	while (42)
	{
	str = readline("minishell>");
	char *exit = "exit";
	char *cpy_str = str;
	while (*cpy_str++ == *exit)
		if (!*exit++)
			return (--exit, free(str), free(test), 0);
	test = scan_expand(str);
	printf("%s\n", test);
	//free(str);
	//free(test);
	}
}
