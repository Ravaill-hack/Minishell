/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:26:14 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/14 16:14:58 by juduchar         ###   ########.fr       */
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
		access();
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
}