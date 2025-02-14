/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:26:14 by lmatkows          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/13 15:56:57 by lmatkows         ###   ########.fr       */
=======
/*   Updated: 2025/02/14 17:38:14 by juduchar         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

// first test with signal handling

#include "minishell.h"

<<<<<<< HEAD
char	**ft_get_env(char **env_shell)
{
	char	**env;
	int		i;

	i = 0;
	env = (char **)malloc(sizeof(char *));
	if (!env)
		return (NULL);
	while (env_shell[i])
	{
		env[i] = ft_strdup(env_shell[i]);

	}
}

t_minishell	*ft_init_var(char **env)
 {
	t_minishell	*var;

	var = (t_minishell *)malloc(sizeof(t_minishell));
	if (!var)
		return (NULL);
	var->env = ft_get_env(env);
	var->line = NULL;
	return (var);
 }

int	main(int argc, char **argv, char **env)
{
	t_minishell	*var;

	(void)argc;
	(void)argv;
	var = ft_init_var(env);
	while (1)
	{
		var->line = readline(PROMPT);
		add_history(var->line);
		//ft_error_line(var->line);
	}
	printf("%s\n", var->line);
	free (var->line);
=======
void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("CTRL + C pressed\n");
		// these functions always have to be together
		// don't interpret the line before has a user input !
		rl_on_new_line();
		// give back the terminal to the user
		rl_redisplay();
	}
}

int	main(void)
{
	// user input
	char	*str;
	printf();
	// handle signal CTRL + C
	signal(SIGINT, handle_signal);
	// get the user input
	str = readline(PROMPT);
	// while a user does not quit the shell
	// TO DO : quit properly with a signal to quit
	// do the signal handler and free all before quit
	// clear history before quit ?
	while (str)
	{
		// TO DO : handle EOF and input from file later
		// check if we have to free str or not if the input is from a file ?
		// TO DO : parser
		if (*str)
		{
			// add the string to the history
			add_history(str);
			printf("You have entered %s\n", str);
			free(str);
		}
		// read a new line from user input
		str = readline(PROMPT);
	}
>>>>>>> main
}