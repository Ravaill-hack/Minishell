/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:26:27 by julien            #+#    #+#             */
/*   Updated: 2025/03/11 11:12:48 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_clear_and_exit(t_var *var, t_shell *shell, int nb_ex)
{
	ft_clear_and_free_all_exit(var, shell);
	exit(nb_ex);
}

int	ft_exit_numeric_arg_err(int i, char **args)
{
	if (ft_isdigit(args[1][i]) == 0
		&& ((i == 0 && args[1][i] != '+' && args[1][i] != '-') || (i != 0)))
		return (1);
	return (0);
}

int	ft_exit_numeric_arg_rq(char **args)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (2);
}

int	ft_exit_too_many_args(char **args)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putstr_fd(": too many arguments\n", 2);
	return (1);
}

int	ft_cmd_exit(t_var *var, t_shell *shell, t_cmd *node)
{
	int	i;

	i = 0;
	ft_putstr_fd("exit\n", 2);
	if (!(node->arg[1]))
		ft_exit_clear_and_exit(var, shell, var->exit_nb);
	else if (node->arg[1][0] == '\0')
		return (2);
	else if (node->arg[2])
		return (ft_exit_too_many_args(node->arg));
	else if (node->arg[1] && !node->arg[2])
	{
		while (node->arg[1][i])
		{
			if (ft_exit_numeric_arg_err(i, node->arg) == 1)
				return (ft_exit_numeric_arg_rq(node->arg));
			i++;
		}
		ft_exit_clear_and_exit(var, shell, ft_atoi(node->arg[1]));
	}
	var->exit_nb = FAILURE;
	return (FAILURE);
}
