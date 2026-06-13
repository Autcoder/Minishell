/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokope <mprokope@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 22:57:31 by mprokope          #+#    #+#             */
/*   Updated: 2026/06/13 04:07:51 by mprokope         ###   ########.fr       */
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
        	return ((env[i] + (ft_strlen(path) + 1)));
		return (NULL);
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

char	**parse_env_to_dict()
{
	extern char	**environ;
	size_t		i;
	size_t		len;
	// char		*tmp;
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

char    *scan_expand(char *str, char **environ)
{
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
	(void)argc;
	(void)argv;
	t_token	*tokens;
	char	*str;
	char	*test;
	char *cpy_str;
	char *exit;
	int	i;

	while (42)
	{
		str = readline("minishell>");
		exit = "exit";
		cpy_str = str;
		while (*cpy_str++ == *exit)
			if (!*exit++)
				return (free(str), free(test), 0);
		test = scan_expand(str, env);
		printf("%s\n", test);
		printf("%zu\n", count_words(str));
		initial_parse(str, &tokens);
		i = 0;
		while (tokens[i].value)
			printf("Token: %s\n", tokens[i++].value);
		//free(str);
		//free(test);
	}
}
