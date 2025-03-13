/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:26:27 by julien            #+#    #+#             */
/*   Updated: 2025/03/13 07:45:53 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_clear_and_exit(t_var *var, t_shell *shell, int nb_ex)
{
	ft_clear_and_free_all_exit(var, shell);
	exit(nb_ex);
}

int	ft_exit_num_arg_rq(char **args)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (2);
}

int	ft_exit_too_many_args(void)
{
	ft_putstr_fd("exit: too many arguments\n", 2);
	return (1);
}

int	ft_cmd_exit(t_var *var, t_shell *shell, t_cmd *node)
{
	ft_putstr_fd("exit\n", 2);
	if (!(node->arg[1]))
		ft_exit_clear_and_exit(var, shell, var->exit_nb);
	else if (node->arg[1][0] == '\0')
		ft_exit_clear_and_exit(var, shell, ft_exit_num_arg_rq(node->arg));
	else if (ft_atol(node->arg[1]) == -1)
		ft_exit_clear_and_exit(var, shell, ft_exit_num_arg_rq(node->arg));
	else if (node->arg[2])
		return (ft_exit_too_many_args());
	else if (ft_atol(node->arg[1]) == -2)
		ft_exit_clear_and_exit(var, shell, 244);
	else if (ft_atol(node->arg[1]) >= 0)
		ft_exit_clear_and_exit(var, shell, ((int)ft_atol(node->arg[1])) % 255);
	var->exit_nb = FAILURE;
	return (FAILURE);
}
