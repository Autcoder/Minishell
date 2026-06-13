/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 10:58:24 by flenski           #+#    #+#             */
/*   Updated: 2026/06/13 10:58:45 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

// TODO: REMOVE BEFORE FINAL PUSH
# ifdef __APPLE__
#  define rl_clear_history clear_history
# endif

/*
TOKEN_WORD,         // cat, ls, -l, filename
TOKEN_PIPE,         // |
TOKEN_REDIRECT_IN,  // <
TOKEN_REDIRECT_OUT, // >
TOKEN_HERE_DOC,     // <<
TOKEN_APPEND,       // >>
*/
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_HERE_DOC,
	TOKEN_APPEND,
}					t_token_type;

/*
FLAG_QUOTED = 1 << 0,   // Inside "" or ''
FLAG_NOEXPAND = 1 << 1, // Inside '' (tells lexer to not touch $VAR)
FLAG_VAR = 1 << 2,      // Contains a $
*/
typedef enum e_token_flags
{
	FLAG_NONE = 0,
	FLAG_QUOTED = 1 << 0,
	FLAG_NOEXPAND = 1 << 1,
	FLAG_VAR = 1 << 2,
}					t_token_flags;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_token_flags	flag;
}					t_token;

char				*get_any(char *env[], char *path);
t_token				*lexer(char *input);

#endif
