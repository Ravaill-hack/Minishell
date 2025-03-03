/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:07:11 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/03 14:21:57 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_need_to_send_in_pipe(t_cmd **cmd_tab, int i_cmd, int nb_cmd)
{
	if (i_cmd == nb_cmd - 1)
		return (0);
	if (cmd_tab[i_cmd]->fd_out.is_def == 1
		|| cmd_tab[i_cmd + 1]->fd_in.is_def == 1)
		return (0);
	return (1);
}

int	ft_need_to_grep_from_pipe(t_cmd **cmd_tab, int i_cmd)
{
	if (i_cmd == 0)
		return (0);
	if (cmd_tab[i_cmd]->fd_in.is_def == 1
		|| cmd_tab[i_cmd - 1]->fd_out.is_def == 1)
		return (0);
	return (1);
}

int	ft_handle_last_cmd(t_var *var, t_shell shell, int i, int frk)
{
	pid_t	pid;

	if (frk == 1)
	{
		pid = fork();
		if (pid == -1)
			return (FAILURE);
		if (pid == 0)
		{
			if (var->cmd[i]->fd_out.fd != 1)
			{
				if (dup2(var->cmd[i]->fd_out.fd, 1) == -1)
					return (FAILURE);
			}
			ft_handle_cmd(var, shell, var->cmd[i]);
			exit(0);
		}
		else
		{
			//ft_putstr_fd("je suis le parent\n", 1);
			if (!waitpid(pid, &var->exit_nb, 0) && var->cmd[i]->fd_out.fd != 1)
				return (close(var->cmd[i]->fd_out.fd), FAILURE);
			if (var->cmd[i]->fd_out.fd != 1)
				close(var->cmd[i]->fd_out.fd);
		}
		return (SUCCESS);
	}
	else
	{
		if (var->cmd[i]->fd_out.fd != 1)
		{
			if (dup2(var->cmd[i]->fd_out.fd, 1) == -1)
				return (FAILURE);
		}
		ft_handle_cmd(var, shell, var->cmd[i]);
		if (var->cmd[i]->fd_out.fd != 1)
			close(var->cmd[i]->fd_out.fd);
		return (SUCCESS);
	}
}

int	ft_handle_regular_cmd(t_var *var, t_shell shell, int i)
{
	pid_t	pid;

	(void)shell;
	pid = fork();
	if (pid == -1)
		return (FAILURE);
	if (pid == 0)
	{
		if (var->cmd[i + 1]->fd_in.fd != 0)
			close(var->cmd[i + 1]->fd_in.fd);
		if (var->cmd[i]->fd_out.fd != 1)
		{
			if (dup2(var->cmd[i]->fd_out.fd, 1) == -1)
				return (FAILURE);
		}
		//ft_handle_cmd(var, shell, var->cmd[i]);
		exit(0);
	}
	else
	{
		if (!waitpid(pid, &(var->exit_nb), 0))
			return(close(var->cmd[i]->fd_out.fd), FAILURE);
		if (var->cmd[i]->fd_out.fd != 1)
			close(var->cmd[i]->fd_out.fd);
		if (var->cmd[i + 1]->fd_in.fd != 0)
		{
			if (dup2(var->cmd[i + 1]->fd_in.fd, 0) == -1)
				return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	ft_handle_pipes(t_var *var, t_shell shell)
{
	int	i;
	int	saved_fd_in;

	i = 0;
	saved_fd_in = dup(STDIN_FILENO);
	if (var->cmd[0]->fd_in.fd != 0)
		if (dup2(var->cmd[0]->fd_in.fd, 0) == -1)
			return (FAILURE);
	if (var->nb_cmd == 1 && ft_is_builtin_cmd(var->cmd[0]) == 1)
		return (dup2(saved_fd_in, STDIN_FILENO), close(saved_fd_in), ft_handle_last_cmd(var, shell, 0, 0));
	else if (var->nb_cmd == 1 && ft_is_builtin_cmd(var->cmd[0]) == 0)
		return (dup2(saved_fd_in, STDIN_FILENO), close(saved_fd_in), ft_handle_last_cmd(var, shell, 0, 1));
	while (i < var->nb_cmd - 1)
	{
		ft_handle_regular_cmd(var, shell, i);
		i++;
	}
	ft_handle_last_cmd(var, shell, i, 1);
	dup2(saved_fd_in, STDIN_FILENO);
	close(saved_fd_in);
	return (SUCCESS);
}
