/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:25:36 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/20 17:47:32 by juduchar         ###   ########.fr       */
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

// read write access close fork dup dup2 pipe isatty ttyname ttyslot chdir getcwd
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


typedef enum	s_line_token
{
	S_LESS,
	D_LESS,
	S_GREAT,
	D_GREAT,
	//O_PAR, --> pour les bonus
	//C_PAR, --> pour les bonus
	//AND, --> pour les bonus
	//OR, --> pour les bonus
	PIPE,
	NL,
	CONTENT,
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

typedef struct	s_token_list
{
	t_line_token			type;
	// t_content_token		content;
	char					*val;
	struct	s_token_list	*prev;
	struct	s_token_list	*next;
}	t_token_list;

typedef struct	s_var
{
	char					*line;
	char					**split_line;
	t_token_list			**token_list;
	char					**env;
	int						exit_nb;
}	t_var;


/*
Initialisation
*/
int				ft_parse_line(t_var *var);
t_token_list	**ft_parse_token_list(char *line, char **env);
/*
Environnement
*/
int				ft_get_line_env(char **env, char *env_var_key);
char			**ft_modify_shlvl(char **env, int lvl);
char			*ft_extract_key_env(char *env_line);
char			*ft_extract_value_env(char *env_line);
/*
Token management
*/
//t_token_list	**ft_build_token_list(char **str);
//t_token_list	*ft_append_token(char *word, t_token_list **list);
t_token_list	*ft_last_token(t_token_list *token);
t_line_token	ft_find_token_type(char *str);
/*
Signal management
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
Cleaning
*/
void			ft_free_line(t_var var);
void			ft_free_token_list_until(t_token_list **list, int n);
void			ft_clear_and_free_all(t_var var);
/*
Utils
*/

/*
Debug
*/
void			ft_print_info_list(t_token_list *list);
void			ft_print_token_type(t_token_list *token);

int				ft_add_env_var(char ***env, char *line);
int				ft_get_line_env(char **env, char *title);

/*
Cmds
*/
char			*ft_strjoin3(char *s1, char *s2, char *s3);
//char			*extract_env(char **env, char *env_var_key);
char			*extract_path(char **env, char *cmd);
char			**ft_set_exec_args(char *path, char **split_cmd);
int				ft_remove_env_var(char ***env_ptr, int line_index);
int				ft_add_env_var(char ***env, char *env_var);
char			*ft_extract_key_env(char *env_var);
char			*ft_extract_value_env(char *env_var);
int				exec_cmd(char **env, char *cmd);
int 			ft_cmd_exit(t_var var, char **env, t_token_list *token_list);
void 			ft_cmd_env(char **env, t_token_list *token_list);
int 			ft_cmd_unset(char ***env_ptr, t_token_list *token_list);
int				ft_cmd_export(char ***env_ptr, t_token_list *token_list);
#endif