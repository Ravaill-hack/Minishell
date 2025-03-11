/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:51:41 by julien            #+#    #+#             */
/*   Updated: 2025/03/11 09:59:31 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE //

#include "minishell.h"

void	ft_error_cmd_not_found(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	ft_exec_error(char **split_cmd)
{
	ft_putstr_fd(split_cmd[0], 2);
	ft_putstr_fd(": ", 2);
	if (split_cmd[1])
	{
		ft_putstr_fd(split_cmd[1], 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(strerror(errno), 1);
	ft_putchar_fd('\n', 1);
}

void	ft_open_error(char *path)
{
	if (path)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
}

void	ft_print_error_hdc(int i, char *heredoc)
{
	ft_putstr_fd("warning: here-document at line ", 2);
	ft_putnbr_fd(i, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(heredoc, 2);
	ft_putstr_fd("')\n", 2);
}
