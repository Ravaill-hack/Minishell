/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 06:56:24 by juduchar          #+#    #+#             */
/*   Updated: 2025/01/20 09:02:36 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

volatile sig_atomic_t	g_sig1_received;

void	handle_sigusr1_reception(int sig)
{
	if (sig == SIGUSR1)
	{
		ft_printf("Message reçu par le serveur\n");
		g_sig1_received = 1;
	}
}

void	set_signal_reception_handler(void)
{
	struct sigaction	sa1;

	sa1.sa_handler = handle_sigusr1_reception;
	sa1.sa_flags = SA_RESTART;
	sigemptyset(&sa1.sa_mask);
	sigaction(SIGUSR1, &sa1, NULL);
}

int	main(int argc, char **argv)
{
	pid_t			server_pid;
	const char		*str;
	size_t			str_len;

	if (argc - 1 == 2)
	{
		set_signal_reception_handler();
		g_sig1_received = 0;
		server_pid = (pid_t)ft_atoi(argv[1]);
		str = argv[2];
		str_len = ft_strlen(str);
		send_bytes_size_t(str_len, server_pid);
		while (*str)
		{
			send_bytes_char(*str, server_pid);
			str++;
		}
		while (!g_sig1_received)
			pause();
	}
}
