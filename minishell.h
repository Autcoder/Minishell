/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 10:58:24 by flenski           #+#    #+#             */
/*   Updated: 2026/08/23 14:20:40 by flink            ###   ########.fr       */
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

extern volatile sig_atomic_t	g_sigint;

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
	int				fd_fail;
}					t_cmd;

// execution
/*
int pipe[2];    	// replaces fd[0] (read) and fd[1] (write)
int prev_fd;    	// replaces fd[2]
int is_builtin; 	// replaces fd[3]
int idx;        	// replaces fd[4] (current command index)
int status_code;	// replaces fd[5]
pid_t p				// replaces *p
*/
typedef struct s_exec
{
	int				pipe[2];
	int				prev_fd;
	int				is_builtin;
}					t_exec;

typedef struct s_data
{
	t_token			*tokens;
	t_cmd			*cmds;
	t_exec			ex;
	char			*str;
	char			**env;
	int				status_code;
	pid_t			*p;
}					t_data;
//Execute helper
void				pipe_fail_clean(t_data *data);
void				put_error(char *name, char *string);
t_cmd				*build_cmds(t_token *tokens, t_data *data);
int					builtin_only(t_data *data, int idx);
void				child_process(t_data *data, int idx);
int					check_access(char *cmd);
int					check_if_word(t_token *tokens, size_t i);
int					check_unclosed_quotes(char *input);
void				close_fd(int fd0, int fd1, int fd2, int fd3);
void				clean_arr(char **env, size_t i);
/* Clean partially full arrays */
void				clean_split(char **split);
void				clean_up(t_data *data);
int					command_not_found(t_data *data, int idx);
size_t				count_and_init_exec(t_cmd *cmds, t_exec *ex);
size_t				count_cmds(t_token *tokens);
size_t				count_words(t_token *tokens, size_t start);
void				dup_and_close(int *fd1, int fd_2_cpy, int fd2);
int					execute(t_data *data);
int					execute_init(t_data *data, char **path);
int					expand_tokens(t_data *data);
t_token				*expand_tokens_parse(t_token *tokens, size_t *cap);
char				*find_path(char *to_find, char *path1);
void				free_all_data(t_data *data);
void				free_cmds(t_cmd *cmds);
void				free_cmds_exec(t_cmd *cmds, size_t count);
void				free_env(char **env);
char				*ft_strnjoin(char const *s1, char const *s2, size_t size);
char				*ft_strnfjoin(char const *s1, char const *s2, size_t size);
void				handle_quotes(t_token *tokens);
int					here_doc(char *eof, t_data *data);
int					init_cmds(t_cmd *cmds, t_token *tokens, size_t i,
						size_t cmd_i);
char				**init_env(void);
int					internal_export(char *name, t_data *data, char *value);
char				*levi(t_data *data, char *str);
t_token				*lexer(char *input);
char				*mesh_tgthr(char *str, char *tmp, size_t old, size_t new);
char				*get_any(char *env[], char *path);
t_token				*get_tokens(char *str);
char				**parse_env_to_dict(char **environ);
void				reset_loop_data(t_data *data);
void				setup_signals(void);
char				*shel_lvl(char **env);
size_t				scan_dollar(char *str, char **key_list);
int					wait_helper(t_data *data);
//levi helpers
char				*apply_function(t_data *data, size_t *i, char *cur, int s);
int					check_quotes(char *quote, char *cur, size_t i);
char				*handle_status_code(char *cur, size_t *i, int status_code);

/*built ins*/
int					run_builtin(t_data *data, int idx);
int					is_builtin(t_cmd cmd);
int					ft_cwd(void);
int					ft_cd(t_data *data, char **cmd);
int					ft_echo(char **cmd);
int					ft_env(t_data *data);
int					ft_exit(t_data *data);
// TODO Fix, multiple vars + export +=smth
int					ft_export(t_data *data, char **argv);
int					ft_unset(t_data *data, char **argv);
//BS
int					set_status_up(int *ret, int *idx, int switcher);
void				yet_another_help(char *ret, size_t s, char *b, size_t *a);
int					expand_levi(t_data *data, char **ret, int i);
char				*levi_here_doc(t_data *data, char *str);
void				expand_here_doc(char **line, t_data *data);
//export helpers
int					export_helper(t_data *data, char *cmd, char *temp);
int					check_word(char *cmd, int *status, size_t *idx);
int					add_var(t_data *data, char *cmd);
int					update_var(t_data *data, char *cmd, char *temp);
int					strchr_but_num(char *str);
int					check_alpha_num(char *str);
//SIGHANDLE
void				handle_sigint(int sig);

#endif
