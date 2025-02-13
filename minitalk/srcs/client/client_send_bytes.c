/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_send_bytes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:22:12 by juduchar          #+#    #+#             */
/*   Updated: 2025/01/23 15:17:23 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	send_byte_to_server(pid_t server_pid, unsigned char byte)
{
	int	signal_to_send;

	if (byte == 0)
		signal_to_send = SIGUSR1;
	else if (byte == 1)
		signal_to_send = SIGUSR2;
	if (kill(server_pid, SIGUSR1) == -1)
	{
		ft_printf("PID invalide ou inaccessible\n");
		return (0);
	}
	if (kill(server_pid, signal_to_send) == -1)
	{
		ft_printf("Erreur lors de l'envoi du bit %d\n", byte);
		return (0);
	}
	usleep(300);
	return (1);
}

void	send_bytes_size_t(size_t n, pid_t server_pid)
{
	unsigned int	size;
	int				i;
	size_t			mask;
	int				byte;

	size = 8 * sizeof(size_t);
	i = size - 1;
	while (i >= 0)
	{
		mask = (size_t)1 << i;
		byte = ((n & mask) != 0);
		if (byte == 0)
			send_byte_to_server(server_pid, 0);
		else if (byte == 1)
			send_byte_to_server(server_pid, 1);
		i--;
	}
}

void	send_bytes_char(unsigned char octet, pid_t server_pid)
{
	int				i;
	unsigned char	byte;

	i = 7;
	while (i >= 0)
	{
		byte = (octet >> i) & 1;
		if (byte == 0)
			send_byte_to_server(server_pid, 0);
		else if (byte == 1)
			send_byte_to_server(server_pid, 1);
		i--;
	}
}
