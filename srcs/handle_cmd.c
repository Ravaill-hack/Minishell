/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:13:42 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/02 12:37:34 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int	ft_set_pipes(t_var *var, t_cmd **cmd_list)
{
	int	i;
	int	fd_pipe[2];

	i = 1;
	if (var->nb_cmd == 1)
		return (SUCCESS);
	if (var->nb_cmd == 2)
		return (ft_set_2_pipes(var, cmd_list));
	while (i < var->nb_cmd)
	{
		if (cmd_list[i]->fd_in.is_def != 1)
		{

		}
	}
	return (SUCCESS);
}
*/

int	ft_handle_pipes(t_var *var, t_shell shell)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (i < var->nb_cmd)
	{
		if ((var->cmd[i])->fd_in.fd != 0)
		{
			if (dup2((var->cmd[i])->fd_in.fd, 0) == -1)
				return (FAILURE);
		}
		if ((var->cmd[i])->fd_out.fd != 1)
		{
			if (dup2((var->cmd[i])->fd_out.fd, 1) == -1)
				return (FAILURE);
		}
		res = ft_handle_cmd(var, shell, var->cmd[i]);
		i++;
	}
	return (res);
}

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
