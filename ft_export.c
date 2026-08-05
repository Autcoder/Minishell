#include "minishell.h"
#include "libft/libft.h"

int	add_var(t_data *data, char *cmd)
{
	size_t	i;

	i = 0;
	while (data->env[i])
		i++;
	data->env = ft_realloc(data->env, sizeof(char *) * i, sizeof(char *) * (i + 2));
	if (!data->env)
		return (1);
	data->env[i++] = ft_strdup(cmd);
	data->env[i] = NULL;
	if (!data->env[i - 1])
		return (1);
	return (0);
}

int	update_var(t_data *data, char *cmd)
{
	size_t	old;
	size_t	i;

	i = 0;
	old = ft_strlen(cmd);
	while (data->env[i] && ft_strncmp(data->env[i], cmd, old))
		i++;
	data->env[i] = ft_realloc(data->env[i], ft_strlen(data->env[i]) + 1, ft_strlen(cmd) + 1);
	if (!data->env[i])
		return (1);
	ft_strlcpy(data->env[i] + old, cmd + old, ft_strlen(cmd) + 1 - old);
	return (0);
}

int     ft_export(t_data *data, char **argv)
{
	size_t	idx;
	char    *temp;

	if (!argv[1])
		return(printf("bip boop, UB incoming..\n"), 67);
	idx = 1;
	while (argv[idx])
	{
		temp = ft_strchr(argv[idx], '=');
		*temp = '\0';
		if (!get_any(data->env, argv[idx]))
		{
			*temp = '=';
			if (add_var(data, argv[idx]))
				return (1);
		}
		else
		{
			*temp = '=';
			if (update_var(data, argv[idx]))
				return (1);
		}
		idx++;
	}
	return (0);
}
