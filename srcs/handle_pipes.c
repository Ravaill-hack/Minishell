/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:07:11 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/10 11:10:31 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_is_cmd(t_cmd *cmd, char **env)
{
	char	*path;

	path = NULL;
	if (!cmd->arg[0])
		return (0);
	if (ft_is_builtin_cmd(cmd))
		return (1);
	path = ft_sub_path(cmd->arg[0]);
	if (!path)
		path = ft_extract_path(env, cmd->arg[0]);
	if (!path)
		return (0);
	free(path);
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

int	ft_exec_one(t_var *var, t_shell *shell, int i)
{
	int	saved_stdout;

	saved_stdout = dup(1);
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
	dup2(saved_stdout, 1);
	return (var->exit_nb);
}

int	ft_handle_regular_cmd(t_var *var, t_shell *shell, int i, pid_t *pid)
{
	int		status;

	status = SUCCESS;
	*pid = fork();
	if (*pid == -1)
		return (FAILURE);
	if (*pid == 0)
	{
		status = ft_exec_one(var, shell, i);
		exit(status);
	}
	else
	{
		if (i > 0 && var->cmd[i]->need_pipe_in == 1)
			close(var->cmd[i - 1]->fd_out.fd);
	}
	return (ft_interpret_status(status));
}

int	ft_single_cmd(t_var *var, t_shell *shell)
{
	int		res;
	pid_t	pid[1];

	if (ft_is_cmd(var->cmd[0], var->env) == 0)
	{
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
