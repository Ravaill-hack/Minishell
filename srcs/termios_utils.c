/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:19:15 by julien            #+#    #+#             */
/*   Updated: 2025/02/18 10:19:17 by julien           ###   ########.fr       */
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