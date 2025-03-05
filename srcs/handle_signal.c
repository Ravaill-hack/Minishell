/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:17:24 by julien            #+#    #+#             */
/*   Updated: 2025/03/05 17:40:20 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_sigquit_reception_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
}

void	ft_set_sigint_reception_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = ft_handle_sigint_reception;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	//sigaddset(&sa.sa_mask, SIGTERM);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL);
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

void	ft_handle_signal_children(void)
{
	struct sigaction	sa;
	//signal(SIGINT, SIG_DFL);
	//sa.sa_handler = ft_test;
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	//sigaction(SIGTSTP, &sa, NULL);
}

void	ft_handle_signal_parent(void)
{
	ft_set_sigquit_reception_handler();
	ft_set_sigint_reception_handler();
}

void	ft_special_signal(int signum)
{
	(void) signum;
	ft_putstr_fd("siginfiinfi\n", 1);
	return;
}

void	ft_handle_special_children(void)
{
	struct sigaction	sa;
	struct sigaction	sa_special;
	//sa.sa_handler = ft_test;
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sa_special.sa_handler = ft_special_signal;
	sa_special.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigemptyset(&sa_special.sa_mask);
	//sigaddset(&sa.sa_mask, SIGINT);
	//sigaddset(&sa.sa_mask, SIGQUIT);
	sigaction(SIGINT, &sa_special, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

