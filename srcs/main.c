/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:26:14 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/16 10:44:06 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// first test with signal handling

#include "minishell.h"

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

int	main(int argc, char **argv, char **env)
{
	// user input
	t_var	var;
	(void) argc;
	(void) argv;
	//printf();
	// handle signal CTRL + C
	signal(SIGINT, handle_signal);
	// get the user input
	var.env = ft_modify_shlvl(ft_chartab_dup(env), 1);
	var.line = readline(PROMPT);
	// while a user does not quit the shell
	// TO DO : quit properly with a signal to quit
	// do the signal handler and free all before quit
	// clear history before quit ?
	while (var.line)
	{
		// TO DO : handle EOF and input from file later
		// check if we have to free str or not if the input is from a file ?
		// TO DO : parser
		ft_parse_line(&var, env);
		if (*(var.line))
		{
			// add the string to the history
			add_history(var.line);
			printf("You have entered %s\n", var.line);
			ft_free_line(var);
		}
		// read a new line from user input
		var.line = readline(PROMPT);
	}
}