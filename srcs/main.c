/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:26:14 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/18 09:41:00 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_disable_echoctl(void)
{
	struct termios	termios_p;

	tcgetattr(STDIN_FILENO, &termios_p);
	termios_p.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);
}

void	ft_enable_echoctl(void)
{
	struct termios	termios_p;

	tcgetattr(STDIN_FILENO, &termios_p);
	termios_p.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);
}

void	ft_handle_sigint_reception(int signum)
{
	if (signum == SIGINT)
	{
		close(STDIN_FILENO);
		open("/dev/tty", O_RDONLY);
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_set_sigint_reception_handler(void)
{
	struct	sigaction	sa;

	sa.sa_handler = ft_handle_sigint_reception;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGTERM);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL);
}

void	ft_set_sigquit_reception_handler(void)
{
	struct	sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
}

void	ft_clear_and_free_all(void)
{
	rl_clear_history();
	ft_enable_echoctl();
}

int	main(void)
{
	char	*str;

	ft_disable_echoctl();
	ft_set_sigquit_reception_handler();
	ft_set_sigint_reception_handler();
	str = readline(PROMPT);
	while (str)
	{
		if (*str)
			add_history(str);
		free(str);
		str = readline(PROMPT);
	}
	ft_clear_and_free_all();
	exit(EXIT_SUCCESS);
}