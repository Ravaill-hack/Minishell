/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:41:23 by julien            #+#    #+#             */
/*   Updated: 2025/03/07 10:31:35 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_cmd(t_var *var, t_shell *shell, t_cmd *node)
{
	// if (!node->arg[0] && shell->while_hdc == 1)
	// 	return (SUCCESS);
	if (!node->arg[0])
		return (FAILURE);
	if (ft_strncmp(node->arg[0], "echo", ft_strlen(node->arg[0])) == 0)
		return (ft_cmd_echo(node, var));
	else if (ft_strncmp(node->arg[0], "env", ft_strlen(node->arg[0])) == 0)
		return (ft_cmd_env(var->env, node));
	else if (ft_strncmp(node->arg[0], "export", ft_strlen(node->arg[0])) == 0)
		return (ft_cmd_export(&var->env, node));
	else if (ft_strncmp(node->arg[0], "exit", ft_strlen(node->arg[0])) == 0)
		return (ft_cmd_exit(var, shell, &var->env, node));
	else if (ft_strncmp(node->arg[0], "unset", ft_strlen(node->arg[0])) == 0)
		return (ft_cmd_unset(&var->env, node));
	else if (ft_strncmp(node->arg[0], "pwd", ft_strlen(node->arg[0])) == 0)
		return (ft_cmd_pwd(var->env, node));
	else if (ft_strncmp(node->arg[0], "cd", ft_strlen(node->arg[0])) == 0)
		return (ft_cmd_cd(&var->env, node));
	else
		return (ft_exec_cmd(var->env, node->arg));
	return (SUCCESS);
}

int	ft_is_builtin_cmd(t_cmd *node)
{
	if (!node->arg[0])
		return (0);
	if (ft_strncmp(node->arg[0], "echo", ft_strlen(node->arg[0])) == 0)
		return (1);
	else if (ft_strncmp(node->arg[0], "env", ft_strlen(node->arg[0])) == 0)
		return (1);
	else if (ft_strncmp(node->arg[0], "export", ft_strlen(node->arg[0])) == 0)
		return (1);
	else if (ft_strncmp(node->arg[0], "exit", ft_strlen(node->arg[0])) == 0)
		return (1);
	else if (ft_strncmp(node->arg[0], "unset", ft_strlen(node->arg[0])) == 0)
		return (1);
	else if (ft_strncmp(node->arg[0], "pwd", ft_strlen(node->arg[0])) == 0)
		return (1);
	else if (ft_strncmp(node->arg[0], "cd", ft_strlen(node->arg[0])) == 0)
		return (1);
	return (0);
}
