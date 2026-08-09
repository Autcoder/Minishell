

#include "minishell.h"
#include "libft/libft.h"

void	put_error(char *name, char *string)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(string, 2);
	write(2, "\n", 1);
}
