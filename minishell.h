#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>
# include <term.h>

typedef enum
{
	FLAG_NONE = 0,//0x0000
	FLAG_QUOTED = 1 << 0,//0x0001
	FLAG_NOEXPAND = 1 << 1,//0x0010
	FLAG_VAR = 1 << 2,//0x0100
}	t_token_flags;

typedef struct
{
	char			*value;
	t_token_flags	flag;
}	t_token;

char	*get_any(char *env[], char *path);
size_t	count_words(char *str);
size_t	initial_parse(char *input, t_token **tokens);

#endif
