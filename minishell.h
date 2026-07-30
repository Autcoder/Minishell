/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 10:58:24 by flenski           #+#    #+#             */
/*   Updated: 2026/07/30 08:13:12 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
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

/*
TOKEN_WORD,         // cat, ls, -l, filename
TOKEN_PIPE,         // |
TOKEN_REDIRECT_IN,  // <
TOKEN_REDIRECT_OUT, // >
TOKEN_HERE_DOC,     // <<
TOKEN_APPEND,       // >>
TOKEN_EOF			// simply delimit
*/
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_HERE_DOC,
	TOKEN_APPEND,
	TOKEN_EOF
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}					t_token;

typedef struct s_cmd
{
	char			**argv;
	char			*path;
	int				fd_in;
	int				fd_out;
}					t_cmd;

// execution
/*
int pipe[2];     // replaces fd[0] (read) and fd[1] (write)
int prev_fd;     // replaces fd[2]
int is_builtin;  // replaces fd[3]
int idx;         // replaces fd[4] (current command index)
int status_code; // replaces fd[5]
*/
typedef struct s_exec
{
	int				pipe[2];
	int				prev_fd;
	int				is_builtin;
	int				idx;
	int				status_code;
}					t_exec;

/*exec*/
int					execute(t_cmd *cmds, char ***env, int status_code);
t_cmd				*build_cmds(t_token *tokens);

int					check_access(char *cmd);
int					check_unclosed_quotes(char *input);
/*Close fd's*/
void				close_fd(int fd0, int fd1, int fd2, int fd3);
/* Clean partially full arrays */
void				clean_split(char **split);
/* For full arrays we have free_ptr_arrays anyways no? */
void				clean_arr(char **env, size_t i);
size_t				count_cmds(t_token *tokens);
size_t				count_words(t_token *tokens, size_t start);
void				expand_tokens(t_token *tokens, char **env, int status_code);
t_token				*expand_tokens_parse(t_token *tokens, size_t *cap);
void				free_cmds(t_cmd *cmds);
char				*ft_strnjoin(char const *s1, char const *s2, size_t size);
char				*ft_strnfjoin(char const *s1, char const *s2, size_t size);
void				handle_quotes(t_token *tokens);
int					here_doc(char *eof);
int					init_cmds(t_cmd *cmds, t_token *tokens, size_t i,
						size_t cmd_i);
char				**init_env(void);
size_t				init_fd_and_count(t_cmd *cmds, int fd[5]);
char				*levi(char *str, char **env, int status_code);
t_token				*lexer(char *input);
char				*get_any(char *env[], char *path);
t_token				*get_tokens(char *str);
char				**parse_env_to_dict(char **environ);
void				setup_signals(void);
int					internal_export(char *name, char ***env, char *value);
char				*shel_lvl(char ***env);
size_t				scan_dollar(char *str, char **key_list);
int					wait_helper(t_cmd *cmds, pid_t **p);

/*built ins*/
int					run_builtin(t_cmd cmd, char ***env, int status_code);
int					is_builtin(t_cmd cmd);
int					ft_cwd(void);
int					ft_cd(char ***env, char *cmd);
int					ft_echo(char **cmd);
int					ft_env(char **env);
int					ft_exit(t_cmd cmd, int *exit_code);
int					ft_export(char ***env, char *cmd);

#endif
