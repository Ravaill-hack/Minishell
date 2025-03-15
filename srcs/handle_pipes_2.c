/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:47:38 by julien            #+#    #+#             */
/*   Updated: 2025/03/15 17:14:26 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE //

#include "minishell.h"

int	ft_need_to_send_in_pipe(t_cmd **cmd_tab, int i_cmd, int nb_cmd)
{
	if (i_cmd == nb_cmd - 1)
		return (0);
	if (cmd_tab[i_cmd]->fd_out.is_def == 1)
		return (0);
	return (1);
}

int	ft_need_to_grep_from_pipe(t_cmd **cmd_tab, int i_cmd)
{
	if (i_cmd == 0)
		return (0);
	if (cmd_tab[i_cmd]->fd_in.is_def == 1)
		return (0);
	return (1);
}

void	ft_close_pipes(t_var *var, int i)
{
	int	j;

	j = 0;
	while (j < var->nb_cmd)
	{
		if (j != i && var->cmd[j]->need_pipe_in == 1
			&& (j - 1) >= 0 && var->cmd[j - 1]->need_pipe_out == 1)
			close(var->cmd[j]->fd_in.fd);
		if (j != i && var->cmd[j]->need_pipe_out == 1)
			close(var->cmd[j]->fd_out.fd);
		j++;
	}
}

int	ft_exec_one(t_var *var, t_shell **shell, int i)
{
	//int	saved_stdout;

	//saved_stdout = dup(1);
	if (i > 0 && var->cmd[i]->need_pipe_in == 1)
		close (var->cmd[i - 1]->fd_out.fd);
	if (i < var->nb_cmd - 1 && var->cmd[i]->need_pipe_out == 1)
		close (var->cmd[i + 1]->fd_in.fd);
	if (var->cmd[i]->fd_in.fd != 0)
	{
		if (dup2(var->cmd[i]->fd_in.fd, 0) == -1)
			return (FAILURE);
		close(var->cmd[i]->fd_in.fd);
	}
	if (var->cmd[i]->fd_out.fd != 1)
	{
		if (dup2(var->cmd[i]->fd_out.fd, 1) == -1)
			return (FAILURE);
		close(var->cmd[i]->fd_out.fd);
	}
	ft_close_pipes(var, i);
	var->exit_nb = ft_handle_cmd(var, shell, var->cmd[i]);
	//dup2(saved_stdout, 1);
	//close (saved_stdout);
	return (var->exit_nb);
}

int	ft_handle_regular_cmd(t_var *var, t_shell **shell, int i, pid_t *pid)
{
	int		status;

	status = SUCCESS;
	pid[i] = fork();
	if (pid[i] == -1)
		return (FAILURE);
	if (pid[i] == 0)
	{
		status = ft_exec_one(var, shell, i);
		ft_clear_and_free_all_exit(var, shell);
		//ft_free_cmd_list(var->cmd);
		if (pid)
			free(pid);
		exit(status);
	}
	else
	{
		if (i > 0 && var->cmd[i]->need_pipe_in == 1)
			close(var->cmd[i - 1]->fd_out.fd);
	}
	return (status);
}
