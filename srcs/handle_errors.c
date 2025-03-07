/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:27:03 by julien            #+#    #+#             */
/*   Updated: 2025/03/07 10:10:37 by juduchar         ###   ########.fr       */
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
