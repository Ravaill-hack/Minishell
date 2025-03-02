/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:13:42 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/02 12:52:44 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_cmd(t_var *var, t_shell shell, t_cmd *node)
{
	(void)shell;
	if (ft_strncmp(node->arg[0], "echo", ft_strlen(node->arg[0])) == 0)
		return (ft_cmd_echo(node, var));
	else if (ft_strncmp(node->arg[0], "env", ft_strlen(node->arg[0])) == 0)
		return (ft_cmd_env(var->env, node));
	else if (ft_strncmp(node->arg[0], "export", ft_strlen(node->arg[0])) == 0)
		return (ft_cmd_export(&var->env, node->arg));
	else if (ft_strncmp(node->arg[0], "exit", ft_strlen(node->arg[0])) == 0)
		return (ft_cmd_exit(*var, shell, &var->env, node));
	// else if (ft_strncmp(val, "unset", 5) == 0)
	// 	return (ft_cmd_unset(&var->env, *(var->token_list)));
	// else if (ft_strncmp(val, "pwd", ft_strlen(val)) == 0)
	// 	return (ft_cmd_pwd(var->env, *(var->token_list)));
	// else if (ft_strncmp(val, "cd", 2) == 0)
	// 	return (ft_cmd_cd(&var->env, *(var->token_list)));
	else
		return (ft_exec_cmd(var->env, node->arg));
	return (SUCCESS);
}
