/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:25:36 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/11 11:15:54 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef FAILURE
#  define FAILURE 1
# endif

# ifndef SUCCESS
#  define SUCCESS 0
# endif

# ifndef VALGRIND_DEBUG
#  define VALGRIND_DEBUG 0
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
# include <errno.h>

extern int	g_while_hd;

typedef enum s_line_token
{
	S_LESS,
	D_LESS,
	S_GREAT,
	D_GREAT,
	PIPE,
	NL,
	CONTENT,
	DOLL,
}	t_line_token;

typedef enum s_type_fd
{
	SIMPLE,
	DOUBLE,
	NONE,
}	t_type_fd;

typedef struct s_cd
{
	char					*home;
	char					*old_pwd;
	int						status;
	char					*new_pwd;
	char					*path;
}	t_cd;

typedef struct s_fd
{
	int						fd;
	t_type_fd				type;
	int						is_def;
}	t_fd;

typedef struct s_cmd
{
	char					**raw;
	int						*is_redir;
	char					**arg;
	char					**chev;
	t_fd					fd_in;
	t_fd					fd_out;
	int						need_pipe_in;
	int						need_pipe_out;
	char					*heredoc;
}	t_cmd;

typedef struct s_token_list
{
	t_line_token			type;
	char					*val;
	int						print_space_after;
	int						dq_start;
	int						dq_end;
	int						sq;
	struct s_token_list		*prev;
	struct s_token_list		*next;
}	t_token_list;

typedef struct s_shell
{
	char					*terminal_prompt;
	char					*prompt;
	int						while_hdc;
}	t_shell;

typedef struct s_var
{
	char					*line;
	char					**split_line;
	t_token_list			**token_list;
	int						**fd_pipe;
	t_cmd					**cmd;
	int						nb_cmd;
	char					**env;
	char					**declare;
	int						exit_nb;
	int						shlvl0;
	int						status;
}	t_var;

typedef struct s_index
{
	int						i;
	int						j;
}	t_index;

/*
Debug (debug.c)
*/
void			ft_print_token_type(t_token_list *token);
void			ft_print_info_list(t_token_list *list, char **env);
void			ft_print_chev(char **chev);
void			ft_print_info_cmd_list(int nb_cmd, t_cmd **list);
/*
Init (init.c)
*/
void			get_prompt(t_var *var, t_shell *shell);
int				ft_update_shlvl(char ***env, int level, t_var *var);
t_shell			*ft_init_shell(void);
char			**ft_create_empty_env(void);
void			ft_init(t_var *var, char **env);
/*
Utils (utils.c)
*/
int				ft_nb_pipes(t_token_list *list);
int				ft_nb_dolls(t_token_list *list);
int				ft_nb_str(t_token_list *list);
/*
Token - append (token_append.c)
*/
t_token_list	*ft_append_content(char *line, int *i, t_token_list **list);
t_token_list	*ft_append_squoted(char *line, int *i, t_token_list **list);
t_token_list	*ft_append_dquoted(char *line, int *i, t_token_list **list);
t_token_list	*ft_append_doll(char *line, int *i, t_token_list **list, int x);
t_token_list	*ft_append_operand(char *line, int *i, t_token_list **list);
/*
Token - parsing (token_parsing.c)
*/
void			ft_handle_dquoted_content(char *line, int *i,
					t_token_list **list, int x);
t_token_list	*ft_deal_dquoted(char *line, int *i,
					t_token_list **list, int x);
int				ft_append_tokens(char *line, t_token_list **list, int nb_x);
t_token_list	**ft_build_token_list(char *line, int nb_x);
int				ft_parse_line(t_var *var, char *prompt, t_shell *shell);
/*
Token - parsing (token_parsing_2.c)
*/
int				ft_doll_var_exists(char *str, char **env);
char			*ft_exit_nb_join(char *str, t_var *var);
char			*ft_replace_doll(char *str, t_var *var);
int				ft_expand_dolls(t_token_list *list, t_var *var);
/*
Token - extract doll (token_extract_doll.c)
*/
char			*ft_handle_question_mark(char *str, int i, int j, char *line);
char			*ft_extract_doll(char *line, int *i, int nb_x);
char			*ft_extract_title_doll(char *str, int *i);
/*
Token - extract content (token_extract_content.c)
*/
char			*ft_extract_content(char *line, int *i);
char			*ft_extract_sq_content(char *line, int *i);
char			*ft_extract_dq_content(char *line, int *i);
/*
Token - token check (token_check.c)
*/
int				ft_is_doll(char *str, int i);
int				ft_is_operand(char *str, int i);
int				ft_is_in_squotes(char *line, int ind);
int				ft_is_in_dquotes(char *line, int ind);
int				ft_is_in_quotes(char *line, int ind);
/*
Token - len (token_len.c)
*/
int				ft_doll_len(char *str, int i);
int				ft_dquoted_len(char *str, int i);
int				ft_squoted_len(char *str, int i);
int				ft_strlen_content(char *str, int i);
int				ft_exit_nb_len(int nb_exit);
/*
Token - utils (token_utils.c)
*/
t_line_token	ft_find_token_type(char *str, int i);
t_token_list	*ft_last_token(t_token_list *token);
void			ft_free_list(t_token_list **list);
void			ft_skip_spaces(char *str, int *i, t_token_list *list);
/*
Token - error (token_error.c)
*/
int				ft_quote_error(char *line);
int				ft_token_redir_error(t_cmd *node, int i); // a faire
int				ft_is_empty_quotes_error(char *prompt);
int				ft_is_error_parsing(char *prompt);
/*
Cmd list - init (cmd_list_init.c)
*/
char			**ft_epure_args_array(char **old, int *tab_redir);
/*
Cmd list - utils (cmd_list_utils.c)
*/
t_token_list	*ft_go_to_cmd_node(t_token_list *list, int i);
char			*ft_dup_operand(t_line_token type);
char			*ft_nb_ex_join(char *str, char *doll, int nb_ex);
int				ft_is_nb_exit(char *str);
char			*ft_dolljoin(char *str, char *doll, char **env);
/*
Cmd list - len (cmd_list_len.c)
*/
size_t			ft_strlen_nb(int n);
int				ft_len_new_array(char **old, int *tab_redir);
int				ft_find_special_len(t_token_list *node, char **env);
int				ft_doll_val_len(char *doll, char **env);
/*
Cmd list - build (cmd_list_build.c)
*/
int				*ft_init_redir_check(t_token_list *node);
char			**ft_token_list_to_char_array(t_token_list *node,
					t_cmd **cmd_node);
t_cmd			*ft_create_cmd_node(t_var *var, int i, t_shell *shell);
t_cmd			**ft_build_cmd_list(t_var *var, t_shell *shell);
t_cmd			**ft_free_cmd_list_until(t_cmd **cmd_list, int n);
/*
Cmd fill arg (cmd_fill_arg.c)
*/
char			*ft_fill_arg_redirs(t_token_list **node);
char			*ft_fill_arg_not_redirs(t_token_list **node);
char			*ft_fill_arg(t_token_list **node);
/*
Cmd fill arg utils (cmd_fill_arg_utils.c)
*/
int				ft_node_is_doll(t_token_list *node);
int				ft_go_to_next_node_condition(t_token_list **node);
int				ft_node_is_not_redir(t_token_list **node);
int				ft_node_is_content(t_token_list **node);
/*
Redirection - build (redirection_build.c)
*/
void			ft_init_fd(t_cmd *node);
int				ft_close_fds(t_cmd *node);
int				ft_fill_fd(t_cmd *node, t_shell *shell);
int				**ft_init_pipes(int nb_pipes);
int				ft_set_pipes(t_cmd **cmd, int nb_cmd, int **pipes);
/*
Redirection - handle (redirection_handle.c)
*/
int				ft_set_infile(char *str, t_cmd *node);
int				ft_set_outfile_append(char *str, t_cmd *node);
int				ft_set_outfile_trunc(char *str, t_cmd *node);
int				ft_while_heredoc(char *line, char *heredoc, t_shell *shell);
int				ft_set_heredoc(char *str, t_cmd *node, t_shell *shell);
/*
Redirection - handle 2 (redirection_handle_2.c)
*/
int				ft_read_while_heredoc(char *line, int i, char *heredoc,
					int pipe1);
/*
Redirection - utils (redirection_utils.c)
*/
int				ft_is_redir_in(int *is_redir, char **raw, int i);
int				ft_is_redir_hdc(int *is_redir, char **raw, int i);
int				ft_is_redir_out_trunc(int *is_redir, char **raw, int i);
int				ft_is_redir_out_append(int *is_redir, char **raw, int i);
int				ft_redir_failure(t_cmd *node, int i);
/*
Print errors (print_errors.c)
*/
void			ft_error_cmd_not_found(char *cmd);
void			ft_exec_error(char **split_cmd);
void			ft_open_error(char *path);
void			ft_print_error_hdc(int i, char *heredoc);
/*
Extract env (extract_env.c)
*/
int				ft_get_line_env(char **env, char *env_var_key);
char			*ft_extract_env_value_from_key(char **env, char *env_var_key);
char			*ft_extract_key_env(char *env_var);
char			*ft_extract_value_env(char *env_var);
/*
Update env (update_env.c)
*/
int				ft_update_env_var_value(char ***env_ptr, int line_index,
					char *value);
int				ft_copy_env_var(char **new_env, char **env_ptr, int *i, int *j);
int				ft_update_env_var(char **new_env, char **env,
					t_index *index, char *value);
/*
Update env (update_env_2.c)
*/
int				ft_update_env_var_value_from_key(char ***env,
					char *key, char *value);
int				ft_add_env_var(char ***env, char *env_var);
int				ft_remove_env_var(char ***env_ptr, int line_index);
/*
Handle signal (handle_signal.c)
*/
void			ft_sigint(int signum);
void			ft_sigquit(int signum);
void			ft_set_signals(void);
int				check_signal(void);
/*
Free (free.c)
*/
void			ft_free_token_list(t_token_list **token_list);
void			ft_free_token_list_until(t_token_list **list, int n);
void			ft_clear_and_free_all(t_var *var, t_shell *shell);
void			ft_clear_and_free_all_exit(t_var *var, t_shell *shell);
void			ft_clear_and_free_while(t_var *var, t_shell *shell);
/*
Free (free_2.c)
*/
void			ft_free_cmd_list(t_cmd **cmd);
/*
Handle pipes (handle_pipes.c)
*/
int				ft_single_cmd(t_var *var, t_shell *shell);
int				ft_handle_all_regular_cmds(t_var *var, t_shell *shell,
					pid_t *pids);
void			ft_close_all_pipes(t_var *var);
int				ft_wait_all_childrens(t_var *var, pid_t *pids);
int				ft_handle_pipes(t_var *var, t_shell *shell);
/*
Handle pipes (handle_pipes_2.c)
*/
int				ft_need_to_send_in_pipe(t_cmd **cmd_tab, int i_cmd, int nb_cmd);
int				ft_need_to_grep_from_pipe(t_cmd **cmd_tab, int i_cmd);
void			ft_close_pipes(t_var *var, int i);
int				ft_exec_one(t_var *var, t_shell *shell, int i);
int				ft_handle_regular_cmd(t_var *var, t_shell *shell,
					int i, pid_t *pid);
/*
Handle pipes (handle_pipes_3.c)
*/
int				ft_is_cmd(t_cmd *cmd, char **env);
/*
Handle cmd (handle_cmd.c)
*/
int				ft_handle_cmd(t_var *var, t_shell *shell, t_cmd *node);
int				ft_is_builtin_cmd(t_cmd *node);
/*
Extract path (extract_path.c)
*/
char			*ft_get_path_with_env_path(char *path_raw, char *cmd);
char			*ft_get_path_with_env_pwd(char **env, char *cmd);
char			*ft_get_path_without_env(char *cmd);
char			*ft_extract_path(char **env, char *cmd);
char			*ft_sub_path(char *str);
/*
Exec cmd (exec_cmd.c)
*/
int				ft_try_exec_with_path(char **env,
					char **split_cmd, char *path, int *status);
int				ft_exec_cmd(char **env, char **split_cmd);
/*
Cmd - echo (cmd_echo.c)
*/
int				ft_line_is_str(char *line);
int				ft_is_valid_n(char *line);
int				ft_line_is_opt_n(char **chartab, int imax);
int				ft_opt_n_enabled(char **chartab);
int				ft_cmd_echo(t_cmd *cmd);
/*
Cmd - env - unset (cmd_env_unset.c)
*/
int				ft_cmd_env(char **env, t_cmd *cmd_node);
int				ft_cmd_unset(char ***env_ptr, t_cmd *node);
/*
Cmd - exit (cmd_exit.c)
*/
void			ft_exit_clear_and_exit(t_var *var, t_shell *shell, int nb_ex);
int				ft_exit_numeric_arg_err(int i, char **args);
int				ft_exit_numeric_arg_rq(char **args);
int				ft_exit_too_many_args(char **args);
int				ft_cmd_exit(t_var *var, t_shell *shell, t_cmd *node);
/*
Cmd - cd (cmd_cd.c)
*/
int				ft_cmd_cd(char ***env, t_cmd *node);
int				ft_cmd_cd_home(char ***env);
int				ft_cmd_cd_minus(char ***env);
int				ft_update_old_pwd(char ***env);
int				ft_update_new_pwd(char ***env, char *new_pwd);
/*
Cmd - cd 2 (cmd_cd_2.c)
*/
char			*ft_cmd_cd_get_path(char *raw_path, char *old_pwd);
char			*ft_cmd_cd_get_old_pwd(char **env);
int				ft_cmd_cd_path(char ***env, char *raw_path);
/*
Cmd - export (cmd_export.c)
*/
int				ft_cmd_export(char ***env_ptr, t_cmd *cmd_node, t_var *var);
int				ft_cmd_export_invalid_id(char **args, int i);
int				ft_cmd_export_with_no_args(char ***env_ptr, t_var *var);
int				ft_cmd_export_with_args(char ***env_ptr, char *arg, t_var *var);
int				ft_cmd_pwd(char **env);
/*
Cmd - export 2 (cmd_export_2.c)
*/
int				ft_is_valid_key(char *str);
int				ft_add_to_declare(char *arg, char **env, char ***declare);
int				ft_cmd_export_print_declare(char **env, int i);

#endif