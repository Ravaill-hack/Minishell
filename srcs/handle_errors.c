/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:27:03 by julien            #+#    #+#             */
/*   Updated: 2025/02/24 12:07:41 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_error()
{
	ft_putstr_fd("Error\n", 2);
}

void	ft_print_error_and_exit(t_var var)
{
	ft_print_error();
	ft_clear_and_free_all(var);
	exit(EXIT_FAILURE);
}