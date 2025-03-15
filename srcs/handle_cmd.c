/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:41:23 by julien            #+#    #+#             */
/*   Updated: 2025/03/15 15:35:02 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE //

#include "minishell.h"

int	ft_handle_cmd(t_var *var, t_shell **shell, t_cmd *node)
{
	if (!node->arg[0])
		return (FAILURE);
	if (ft_strncmp(node->arg[0], "echo", 4) == 0 && !node->arg[0][4])
		return (ft_cmd_echo(node));
	else if (ft_strncmp(node->arg[0], "env", 3) == 0 && !node->arg[0][3])
		return (ft_cmd_env(var->env, node));
	else if (ft_strncmp(node->arg[0], "export", 6) == 0 && !node->arg[0][6])
		return (ft_cmd_export(&var->env, node, var));
	else if (ft_strncmp(node->arg[0], "exit", 4) == 0 && !node->arg[0][4])
		return (ft_cmd_exit(var, shell, node));
	else if (ft_strncmp(node->arg[0], "unset", 5) == 0 && !node->arg[0][5])
		return (ft_cmd_unset(&var->env, node));
	else if (ft_strncmp(node->arg[0], "pwd", 3) == 0 && !node->arg[0][3])
		return (ft_cmd_pwd(var->env));
	else if (ft_strncmp(node->arg[0], "cd", 2) == 0 && !node->arg[0][2])
		return (ft_cmd_cd(&var->env, node));
	else
		return (ft_exec_cmd(var->env, node->arg));
	return (SUCCESS);
}

int	ft_is_builtin_cmd(t_cmd *node)
{
	if (!node->arg[0])
		return (0);
	if (ft_strncmp(node->arg[0], "echo", 4) == 0 && !node->arg[0][4])
		return (1);
	else if (ft_strncmp(node->arg[0], "env", 3) == 0 && !node->arg[0][3])
		return (1);
	else if (ft_strncmp(node->arg[0], "export", 6) == 0 && !node->arg[0][6])
		return (1);
	else if (ft_strncmp(node->arg[0], "exit", 4) == 0 && !node->arg[0][4])
		return (1);
	else if (ft_strncmp(node->arg[0], "unset", 5) == 0 && !node->arg[0][5])
		return (1);
	else if (ft_strncmp(node->arg[0], "pwd", 3) == 0 && !node->arg[0][3])
		return (1);
	else if (ft_strncmp(node->arg[0], "cd", 2) == 0 && !node->arg[0][2])
		return (1);
	return (0);
}
