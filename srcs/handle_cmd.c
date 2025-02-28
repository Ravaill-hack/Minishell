/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:13:42 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/28 11:10:53 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_pipes(t_var *var, t_shell shell)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (i < var->nb_cmd)
	{
		res = ft_handle_cmd(var, shell, var->cmd[i]);
		i++;
	}
	return (res);
}

int	ft_handle_cmd(t_var *var, t_shell shell, t_cmd *cmd_node)
{
	(void)shell;
	if (ft_strncmp(cmd_node->arg[0], "echo", 4) == 0)
		return (ft_cmd_echo(cmd_node, var));
	// else if (ft_strncmp(val, "exit", ft_strlen(val)) == 0)
	// 	return (ft_cmd_exit(*var, shell, &var->env, *(var->token_list)));
	// else if (ft_strncmp(val, "env", ft_strlen(val)) == 0)
	// 	ft_cmd_env(var->env, *(var->token_list));
	// else if (ft_strncmp(val, "unset", 5) == 0)
	// 	return (ft_cmd_unset(&var->env, *(var->token_list)));
	// else if (ft_strncmp(val, "export", 6) == 0)
	// 	return (ft_cmd_export(&var->env, *(var->token_list)));
	// else if (ft_strncmp(val, "pwd", ft_strlen(val)) == 0)
	// 	return (ft_cmd_pwd(var->env, *(var->token_list)));
	// else if (ft_strncmp(val, "cd", 2) == 0)
	// 	return (ft_cmd_cd(&var->env, *(var->token_list)));
	else
		return (ft_exec_cmd(var->env, cmd_node->arg));
	return (SUCCESS);
}
