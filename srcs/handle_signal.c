/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:17:24 by julien            #+#    #+#             */
/*   Updated: 2025/03/05 22:00:44 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_sigquit_parent(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
}

void	ft_set_sigint_parent(void)
{
	struct sigaction	sa;

	sa.sa_handler = ft_handle_sigint_parent;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL);
}

void	ft_handle_sigint_parent(int signum)
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

void	ft_set_sigint_sigquit_children(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	ft_set_sigint_sigquit_parent(void)
{
	ft_set_sigquit_parent();
	ft_set_sigint_parent();
}

/*
void	ft_handle_ctrl_d_signal(int signum)
{
	(void) signum;
	return ;
}
*/