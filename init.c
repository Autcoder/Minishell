#include "minishell.h"
#include "libft/libft.h"

/*
 *In case that env is empty, returns 1
 *Otherwise returns SHLVL + 1
 *
 *Return is always Mallocated!
 * */
char	*shel_lvl(char ***env)
{
	char	*str;

	str = get_any(*env, "SHLVL");
	if (!str)
		return (ft_strdup("1"));
	else
		return (ft_itoa(ft_atoi(str) + 1));
}

/*
 * name should always be Nonmallocated.
 * value should always be mallocated, it will be freed internaly
 * in case of error function will return 1
 * */
int	internal_export(char *name, char ***env, char *value)
{
	char	*str;

	if (!value)
		return (1); //TODO we should prbl do global clean up
					//if smth breaks, just exit
	str = ft_strjoin(name, value);
	if (!str)
		return (free(value), 1);
	ft_export(env, str);
	free(str);
	free(value);
	return (0);
}
