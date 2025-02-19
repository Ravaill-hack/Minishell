/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:25:36 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/19 08:28:08 by julien           ###   ########.fr       */
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
	O_PAR,
	C_PAR,
	AND,
	OR,
	PIPE,
	CONTENT,
}	t_line_token;

typedef enum	s_content_token
{
	STR,
	CHAR,
	INT,
	DOL,
	STAR,
	SLSH,
}	t_content_token;

typedef struct	s_token_list
{
	t_line_token			token;
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
	//int					shlvl_0;
	int						exit_nb;
}	t_var;


/*
Initialisation
*/
int				ft_parse_line(t_var *var);
/*
Environnement
*/
int				ft_get_line_env(char **env, char *title);
char			**ft_modify_shlvl(char **matrix, int ind);
/*
Token management
*/
t_token_list	**ft_build_token_list(char **str);
t_token_list	*ft_append_token(char *word, t_token_list **list);
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
char			**ft_chartab_dup(char **matrix);
int				ft_nb_lines(char **matrix);
void			ft_free_tab(char **matrix, int ind);

#endif