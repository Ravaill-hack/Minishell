/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:07:11 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/05 13:55:53 by lmatkows         ###   ########.fr       */
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

int	ft_interpret_status(int	status)
{
	int	exit_nb;

	if (status == 0) //succes
		return (SUCCESS);
	else if (status == 1) //erreur generale
		return (FAILURE);
	else if (status == 2) //mauvaise utilisation de la commande ex cd sans argument valide
		return (FAILURE);
	else if (status == 126) //commande trouvee mais non executable (droits)
		return (FAILURE);
	else if (status == 127) //commande n'a pas ete trouvee
		return (FAILURE);
	else if (status == 128) //commande interrompue avec CTRL D dans un eof
		return (FAILURE);
	else if (status == 130) //commande interrompue avec CTRL C dans un eof
		return (FAILURE);
	else if (status == 131) //commande interrompue avec CTRL \ dans un eof -->tue le processus salement
		return (FAILURE);
	exit_nb = SUCCESS;
	return (exit_nb);
}

int	ft_exec_one(t_var *var, t_shell *shell, int i)
{
	int	status;

	status = SUCCESS;
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
	status = ft_handle_cmd(var, shell, var->cmd[i]);
	return (status);
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
		ft_handle_signal_children();
		status = ft_exec_one(var, shell, i);
		exit(status);
	}
	else
	{
		if (i > 0 && var->cmd[i]->need_pipe_in == 1)
			close(var->cmd[i - 1]->fd_out.fd);
		//if (i < var->nb_cmd - 1 && var->cmd[i - 1]->need_pipe_out == 1)
		//	close(var->cmd[i]->fd_in.fd);
	}
	return (ft_interpret_status(status));
}

int	ft_is_cmd(t_cmd *cmd, char **env)
{
	char	*path;

	path = NULL;
	if (!cmd->arg[0])
	 	return (0);
	if (ft_is_builtin_cmd(cmd))
		return (1);
	path = ft_extract_path(env, cmd->arg[0]);
	if (!path)
		return (0);
	return (1);
}

int	ft_single_cmd(t_var *var, t_shell *shell)
{
	int		res;
	pid_t	pid[1];

	if (ft_is_cmd(var->cmd[0], var->env) == 0)
		return (FAILURE);
	else if (ft_is_builtin_cmd(var->cmd[0]) == 1)
		res = ft_exec_one(var, shell, 0);
	else
	{
		res = ft_handle_regular_cmd(var, shell, 0, &pid[0]);
		waitpid(pid[0], &res, 0);
	}
	return (ft_interpret_status(res));
}

int	ft_handle_pipes(t_var *var, t_shell *shell)
{
	int		i;
	int		status;
	pid_t	pids[var->nb_cmd];

	i = 0;
	if (var->nb_cmd == 1)
	{
		status = ft_single_cmd(var, shell);
		return (ft_interpret_status(status));
	}
	while (i < var->nb_cmd)
	{
		status = ft_handle_regular_cmd(var, shell, i, &pids[i]);
		i++;
	}
	i = 0;
	while (i < var->nb_cmd)
	{
		waitpid(pids[i], &status, 0);
		if (ft_interpret_status(status) == FAILURE)
			return (FAILURE);
		i++;
	}
	return(SUCCESS);
}
