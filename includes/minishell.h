/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:25:36 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/27 11:30:53 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef PROMPT
#  define PROMPT "minishell$ "
# endif

# ifndef FAILURE
#  define FAILURE 0
# endif

# ifndef SUCCESS
#  define SUCCESS 1
# endif

// read write access close fork dup dup2 pipe isatty ttyname
// ttyslot chdir getcwd
# include <unistd.h>
// open
# include <fcntl.h>
// malloc free getenv exit
# include <stdlib.h>
// strerror
# include <string.h>
// printf
# include <stdio.h>
// readline rl_clear_history rl_on_new_line rl_replace_line rl_redisplay
# include <readline/readline.h>
// add_history
# include <readline/history.h>
// signal sigaction sigemtyset sigaddset kill
# include <signal.h>
// fork wait waitpid wait3 wait4 stat
# include <sys/types.h>
// wait waitpid wait3 wait4
# include <sys/wait.h>
// stat lstat fstat
# include <sys/stat.h>
// opendir readdir closedir
# include <dirent.h>
// perror
# include <errno.h>
// tcsetattr tcgetattr
# include <termios.h>
// tgetent tgetflag tgetnum tgetstr tgoto tputs
# include <term.h>
// tgetent tgetflag tgetnum tgetstr tgoto tputs
# include <curses.h>
# include "libft.h"
# include "get_next_line.h"

typedef enum s_line_token
{
	S_LESS,
	D_LESS,
	S_GREAT,
	D_GREAT,
	/*
	O_PAR, --> pour les bonus
	C_PAR, --> pour les bonus
	AND, --> pour les bonus
	OR, --> pour les bonus
	*/
	PIPE,
	NL,
	CONTENT,
	DOLL,
}	t_line_token;

/*
typedef enum	s_content_token
{
	STR,
	CHAR,
	INT,
	DOL,
	STAR,
	SLSH,
}	t_content_token;
*/

typedef enum s_type_fd
{
	SIMPLE,
	DOUBLE,
}	t_type_fd;

typedef struct s_fd
{
	int						fd;
	t_type_fd				type;
	int						is_def;
}	t_fd;

typedef struct s_cmd
{
//	char					*path;
//	char					*name;
	char					**raw;
	char					**arg;
	char					**chev;
	char					*cmd;
	t_fd					fd_in[500];
	t_fd					fd_out[500];
	char 					*heredoc;
}	t_cmd;

typedef struct s_token_list
{
	t_line_token			type;
	char					*val;
	int						print_space_after;
	int						dq_start;
	int						dq_end;
	struct s_token_list		*prev;
	struct s_token_list		*next;
}	t_token_list;

typedef struct s_var
{
	char					*line;
	char					**split_line;
	t_token_list			**token_list;
	t_cmd					**cmd;
	int						nb_cmd;
	char					**env;
	int						exit_nb;
}	t_var;

/*
Init
*/
void			ft_init(t_var *var, char **env);
/*
Token - append
*/
t_token_list	*ft_append_content(char *line, int *i, t_token_list **list);
t_token_list	*ft_append_squoted(char *line, int *i, t_token_list **list);
t_token_list	*ft_append_dquoted(char *line, int *i, t_token_list **list);
t_token_list	*ft_append_doll(char *line, int *i, t_token_list **list);
t_token_list	*ft_append_operand(char *line, int *i, t_token_list **list);
/*
Token - checks
*/
int				ft_is_doll(char *str, int i);
int				ft_is_operand(char *str, int i);
int				ft_is_in_squotes(char *line, int ind);
int				ft_is_in_dquotes(char *line, int ind);
int				ft_is_in_quotes(char *line, int ind);
int				ft_is_nb_exit(char *str);
/*
Token - extract
*/
char			*ft_extract_content(char *line, int *i);
char			*ft_extract_sq_content(char *line, int *i);
char			*ft_extract_dq_content(char *line, int *i);
char			*ft_extract_doll(char *line, int *i);
char			*ft_extract_title_doll(char *str, int *i);
/*
Token - errors
*/
int				ft_quote_error(char *line);
/*
Token - len
*/
int				ft_doll_len(char *str, int i);
int				ft_dquoted_len(char *str, int i);
int				ft_squoted_len(char *str, int i);
int				ft_strlen_content(char *str, int i);
/*
Token - parsing
*/
t_token_list	*ft_deal_dquoted(char *line, int *i, t_token_list **list);
int				ft_append_tokens(char *line, t_token_list **list);
t_token_list	**ft_build_token_list(char *line);
int				ft_parse_line(t_var *var);
/*
Token - utils
*/
t_line_token	ft_find_token_type(char *str, int i);
t_token_list	*ft_last_token(t_token_list *token);
void			ft_free_list(t_token_list **list);
void			ft_skip_spaces(char *str, int *i, t_token_list *list);
/*
Cmd list - init A  TRIER
*/
t_cmd			**ft_build_cmd_list(t_var *var);
t_cmd			*ft_create_cmd_node(t_var *var, int i);
char			**ft_token_list_to_char_array(t_token_list *node);
char			*ft_fill_arg(t_token_list *node);
t_token_list	*ft_go_to_cmd_node(t_token_list	*list, int i);
int				ft_find_special_len(t_token_list *node, char **env);
char			*ft_dolljoin(char *str, char *doll, char **env);
int				ft_doll_val_len(char *doll, char **env);
t_token_list	*ft_go_to_next_node(t_token_list *node);
/*
Handle errors
*/
void			ft_exit_error(t_var var);
/*
Extract env
*/
int				ft_get_line_env(char **env, char *env_var_key);
char			*ft_extract_env_value_from_key(char **env, char *key);
char			*ft_extract_key_env(char *env_var);
char			*ft_extract_value_env(char *env_var);
/*
Update env
*/
int				ft_update_env_var_value(char ***env_ptr, int line_index,
					char *value);
int				ft_copy_env_var(char **new_env, char **env_ptr, int *i, int *j);
int				ft_update_env_var(char **new_env, char **env_ptr,
					int *indices, char *value);
int				ft_add_env_var(char ***env, char *env_var);
int				ft_remove_env_var(char ***env_ptr, int line_index);
char			**ft_modify_shlvl(char **env, int lvl);
/*
Handle signal
*/
void			ft_set_sigquit_reception_handler(void);
void			ft_set_sigint_reception_handler(void);
void			ft_handle_sigint_reception(int signum);
/*
Termios
*/
void			ft_disable_echoctl(void);
void			ft_enable_echoctl(void);
/*
Free
*/
void			ft_free_line(t_var var);
void			ft_free_token_list_until(t_token_list **list, int n);
void			ft_clear_and_free_all(t_var var);
void			ft_free_char_array(char **chartab, int imax);
void			ft_free_cmd_node(t_cmd *node);
void			ft_free_cmd_list(t_var *var, t_cmd **list, int imax);
/*
Debug
*/
void			ft_print_token_type(t_token_list *token);
void			ft_print_info_list(t_token_list *list, char **env);
void			ft_print_info_cmd_list(int nb_cmd, t_cmd **list);
/*
Utils
*/
char			*ft_strjoin3(char *s1, char *s2, char *s3);
int				ft_nb_pipes(t_token_list *list);
int				ft_nb_dolls(t_token_list *list);
int				ft_nb_str(t_token_list *list);
int				ft_doll_var_exists(char *str, char **env);
/*
Handle cmd
*/
int				ft_handle_cmd(t_var *var, char *val);
/*
Exec cmd
*/
char			*ft_extract_path(char **env, char *cmd);
char			**ft_set_exec_args(char *path, char **split_cmd);
int				ft_exec_cmd(char **env, char *cmd);
/*
Cmds
*/
int				ft_cmd_exit(t_var var, char **env, t_token_list *token_list);
int				ft_handle_exit_last_shlvl(t_var var, char **env);
int				ft_handle_exit_not_last_shlvl(char **env);
void			ft_cmd_env(char **env, t_token_list *token_list);
int				ft_cmd_unset(char ***env_ptr, t_token_list *token_list);
int				ft_cmd_export(char ***env_ptr, t_token_list *token_list);
int				ft_cmd_export_with_no_args(char ***env_ptr);
int				ft_cmd_export_with_args(char ***env_ptr, char *arg);
int				ft_cmd_pwd(char **env, t_token_list *token_list);
int				ft_cmd_cd(char **env, t_token_list *token_list);
int				ft_cmd_cd_home(char **env);
int				ft_cmd_cd_path(char **env, char *path);
int				ft_cmd_skip_name(char *str);
int				ft_cmd_echo_print_str(char *str, int i, int opt);
int				ft_cmd_echo_print_doll(t_token_list *token, char **env,
					int exit_nb);
int				ft_cmd_echo_print_tokens(t_token_list *token, int i,
					char **env, int ex_nb);
int				ft_cmd_echo(t_token_list *token_list, char **env, int ex_nb);

#endif