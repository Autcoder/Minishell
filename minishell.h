/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 10:58:24 by flenski           #+#    #+#             */
/*   Updated: 2026/06/23 13:46:23 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
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

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}					t_token;

int					check_unclosed_quotes(char *input);
void				expand_tokens(t_token *tokens, char **env);
void				handle_quotes(t_token *tokens);
char				**init_env(void);
char				*levi(char *str, char **env);
t_token				*lexer(char *input);
int					missfit_check(char *str);
char				*get_type_name(t_token_type type);
void				print_tokens(t_token *tokens);
char				*get_any(char *env[], char *path);
char				*ft_strnjoin(char const *s1, char const *s2, size_t size);
char				*ft_strnfjoin(char const *s1, char const *s2, size_t size);
char				**parse_env_to_dict(char **environ);

#endif
