/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:27:03 by julien            #+#    #+#             */
/*   Updated: 2025/03/08 18:33:15 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_msg_error(char *error_msg)
{
	ft_putstr_fd(error_msg, 2);
}

void	ft_print_error(void)
{
	//ft_putstr_fd("Error\n", 2);
	return ;
}

void	ft_print_error_and_exit(t_var var, t_shell shell)
{
	ft_print_error();
	ft_clear_and_free_all(&var, &shell);
	exit(EXIT_FAILURE);
}

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
