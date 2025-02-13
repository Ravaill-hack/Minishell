/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:07:55 by juduchar          #+#    #+#             */
/*   Updated: 2025/02/13 10:39:21 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "./../ft_printf/includes/ft_printf.h"

typedef struct s_signal_data
{
	pid_t			client_pid;
	unsigned int	bytes_received;
	unsigned char	*str;
	size_t			str_len;
	unsigned char	c;
	size_t			i;
}	t_signal_data;

int		calculate_strlen(t_signal_data *data, unsigned char byte_value);
int		add_char_to_str(t_signal_data *data, unsigned char byte_value);
void	reset_signal_data(t_signal_data *data);
void	handle_signal(int sig, siginfo_t *info, void *context);

#endif