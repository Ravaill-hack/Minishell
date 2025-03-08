/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:26:27 by julien            #+#    #+#             */
/*   Updated: 2025/03/08 18:12:52 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_exit(t_var *var, t_shell *shell, t_cmd *node)
{
	ft_putstr_fd("exit\n", 2);
	if (!(node->arg[1]))
	{
		ft_clear_and_free_all_exit(var, shell);
		exit(var->exit_nb);
	}
	else if (node->arg[1] && !node->arg[2])
	{
		ft_clear_and_free_all_exit(var, shell);
		exit(ft_atoi(node->arg[1]));
	}
	var->exit_nb = FAILURE;
	return (FAILURE);
}
