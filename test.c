/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 15:26:07 by flenski           #+#    #+#             */
/*   Updated: 2026/06/22 15:26:08 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// char	*scan_expand(char *str, char **env)
// {
// 	char	**key_list;
// 	size_t	i;
// 	char	*temp;
// 	char	*ret;

// 	key_list = parse_env_to_dict(); // returns null ended **
// 	if (!key_list)
// 		return (NULL);
// 	temp = ft_strchr(str, '$');
// 	if (!temp)
// 		return (/*TODO tf i return (when it couldn't find anything*/));
// 	i = 0;
// 	while (*str)
// 	{
// 		ret = ft_strnjoin(ret, str, temp - str);
// 		count = // TODO later finish with cuting the string before and after the
// 				//  $VAR and glue it back together using strjoin;
// 			if ()
// 	}
// }
