/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:27:03 by julien            #+#    #+#             */
/*   Updated: 2025/02/21 17:41:48 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_error(t_var var)
{
	ft_putstr_fd("Error\n", 2);
	ft_clear_and_free_all(var);
	exit(EXIT_FAILURE);
}
