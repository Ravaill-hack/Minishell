/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:26:27 by julien            #+#    #+#             */
/*   Updated: 2025/03/10 10:56:58 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_exit(t_var *var, t_shell *shell, t_cmd *node)
{
	int	i;

	i = 0;
	ft_putstr_fd("exit\n", 2);
	if (!(node->arg[1]))
	{
		ft_clear_and_free_all_exit(var, shell);
		exit(var->exit_nb);
	}
	else if (node->arg[1][0] == '\0')
		return (2);
	else if (node->arg[2])
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(node->arg[1], 2);
		ft_putstr_fd(": too many arguments\n", 2);
		return (1);
	}
	else if (node->arg[1] && !node->arg[2])
	{
		while (node->arg[1][i])
		{
			if (ft_isdigit(node->arg[1][i]) == 0)
			{
				if ((i == 0 && node->arg[1][i] != '+'
					&& node->arg[1][i] != '-')
					|| i != 0)
				{
					ft_putstr_fd("exit: ", 2);
					ft_putstr_fd(node->arg[1], 2);
					ft_putstr_fd(": numeric argument required\n", 2);
					return (2);
				}
			}
			i++;
		}
		ft_clear_and_free_all_exit(var, shell);
		exit(ft_atoi(node->arg[1]));
	}
	var->exit_nb = FAILURE;
	return (FAILURE);
}
