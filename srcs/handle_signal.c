/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:17:24 by julien            #+#    #+#             */
/*   Updated: 2025/03/10 10:44:03 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE //

#include "minishell.h"

void	ft_sigint(int signum)
{
	(void)signum;
	if (g_while_hd == 1)
	{
		g_while_hd = 0;
		rl_replace_line("", 1);
		rl_on_new_line();
		ft_putstr_fd("^C\n", 1);
		rl_done = 1;
	}
	else if (waitpid(-1, NULL, WNOHANG) == -1)
	{
		ft_putstr_fd("^C\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		ft_putchar_fd('\n', 2);
}

void	ft_sigquit(int signum)
{
	(void) signum;
	if (g_while_hd == 1)
		return ;
	else if (waitpid(-1, NULL, WNOHANG) != -1)
		ft_putstr_fd("Quit (core dumped)\n", 2);
}

void	ft_set_signals(void)
{
	signal (2, ft_sigint);
	signal (3, ft_sigquit);
}
