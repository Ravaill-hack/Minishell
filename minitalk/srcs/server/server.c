/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 06:56:33 by juduchar          #+#    #+#             */
/*   Updated: 2025/01/15 17:21:35 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	calculate_strlen(t_signal_data *data, unsigned char byte_value)
{
	data->str_len = (data->str_len << 1) | byte_value;
	data->bytes_received++;
	if (data->bytes_received == (8 * sizeof(size_t)))
	{
		data->bytes_received = 0;
		return (1);
	}
	return (0);
}

int	add_char_to_str(t_signal_data *data, unsigned char byte_value)
{
	data->c = (data->c << 1) | byte_value;
	data->bytes_received++;
	if (data->bytes_received == (8 * sizeof(unsigned char)))
	{
		data->str[data->i++] = data->c;
		data->bytes_received = 0;
		data->c = 0;
	}
	return (data->i == data->str_len);
}

void	reset_signal_data(t_signal_data *data)
{
	data->client_pid = 0;
	data->bytes_received = 0;
	data->str_len = 0;
	data->c = 0;
	data->i = 0;
	if (data->str)
	{
		free(data->str);
		data->str = NULL;
	}
}

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	unsigned char			byte_value;
	static t_signal_data	data = {0};

	(void)context;
	data.client_pid = info->si_pid;
	if (sig == SIGUSR1)
		byte_value = 0;
	else if (sig == SIGUSR2)
		byte_value = 1;
	else
		return ;
	if (!data.str)
	{
		if (!calculate_strlen(&data, byte_value))
			return ;
		data.str = malloc((data.str_len + 1) * sizeof(unsigned char));
	}
	else if (add_char_to_str(&data, byte_value))
	{
		data.str[data.i] = '\0';
		ft_printf("%s\n", data.str);
		kill(data.client_pid, SIGUSR1);
		reset_signal_data(&data);
	}
}

int	main(void)
{
	pid_t				server_pid;
	struct sigaction	sa;

	server_pid = getpid();
	ft_printf("%d\n", server_pid);
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
