/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:07:11 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/13 14:43:29 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE //

#include "minishell.h"

int	ft_single_cmd(t_var *var, t_shell *shell)
{
	int		res;
	pid_t	pid[1];

	if (ft_is_cmd(var->cmd[0], var->env) == 0)
	{
		// TO DO : is a directory
		ft_putstr_fd(var->cmd[0]->arg[0], 2);
		ft_putstr_fd(": command not found.\n", 2);
		return (127);
	}
	else if (ft_is_builtin_cmd(var->cmd[0]) == 1)
		res = ft_exec_one(var, shell, 0);
	else
	{
		res = ft_handle_regular_cmd(var, shell, 0, &pid[0]);
		waitpid(pid[0], &res, 0);
		if (res != 0)
			return (res % 255);
	}
	return (res);
}

int	ft_handle_all_regular_cmds(t_var *var, t_shell *shell, pid_t *pids)
{
	int	i;
	int	status;

	i = 0;
	while (i < var->nb_cmd)
	{
		status = ft_handle_regular_cmd(var, shell, i, &pids[i]);
		i++;
	}
	return (status);
}

void	ft_close_all_pipes(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->nb_cmd - 1)
	{
		if (var->cmd[i]->fd_out.fd != 1)
			close(var->cmd[i]->fd_out.fd);
		if (var->cmd[i + 1]->fd_in.fd != 0)
			close(var->cmd[i + 1]->fd_in.fd);
		i++;
	}
}

int	ft_wait_all_childrens(t_var *var, pid_t *pids)
{
	int	i;
	int	status;

	i = 0;
	status = SUCCESS;
	while (i < var->nb_cmd)
	{
		waitpid(pids[i], &status, 0);
		if (status != SUCCESS)
			return (status);
		i++;
	}
	return (status);
}

int	ft_handle_pipes(t_var *var, t_shell *shell)
{
	int		status;
	pid_t	*pids;

	status = SUCCESS;
	if (var->nb_cmd == 1)
		return (ft_single_cmd(var, shell));
	pids = (pid_t *)ft_calloc(var->nb_cmd, sizeof(pid_t));
	status = ft_handle_all_regular_cmds(var, shell, pids);
	ft_close_all_pipes(var);
	status = ft_wait_all_childrens(var, pids);
	free(pids);
	return (status);
}
