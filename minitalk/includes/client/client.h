/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 07:03:36 by juduchar          #+#    #+#             */
/*   Updated: 2025/01/20 09:02:03 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <stddef.h>
# include <unistd.h>
# include <signal.h>
# include "ft_printf.h"

size_t	ft_strlen(const char *s);
int		ft_isspace(int c);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
void	handle_sigusr1_reception(int sig);
void	set_signal_reception_handler(void);
int		send_byte_to_server(pid_t server_pid, unsigned char byte);
void	send_bytes_size_t(size_t n, pid_t server_pid);
void	send_bytes_char(unsigned char octet, pid_t server_pid);

#endif