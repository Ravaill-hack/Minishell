/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:07:11 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/04 17:05:30 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_need_to_send_in_pipe(t_cmd **cmd_tab, int i_cmd, int nb_cmd)
{
	if (i_cmd == nb_cmd - 1)
		return (0);
	if (cmd_tab[i_cmd]->fd_out.is_def == 1
		/*|| cmd_tab[i_cmd + 1]->fd_in.is_def == 1*/)
		return (0);
	return (1);
}

int	ft_need_to_grep_from_pipe(t_cmd **cmd_tab, int i_cmd)
{
	if (i_cmd == 0)
		return (0);
	if (cmd_tab[i_cmd]->fd_in.is_def == 1
		/*|| cmd_tab[i_cmd - 1]->fd_out.is_def == 1*/)
		return (0);
	return (1);
}

int	ft_handle_last_cmd(t_var *var, t_shell shell, int i, int frk)
{
	pid_t	pid;
	int		res;

	if (ft_is_cmd(var->cmd[i], var->env) == 0)
		return (FAILURE);
	if (frk == 1)
	{
		pid = fork();
		if (pid == -1)
			return (FAILURE);
		if (pid == 0)
		{
			signal(SIGINT, SIG_IGN);
			if (var->cmd[i]->fd_out.fd != 1)
			{
				if (dup2(var->cmd[i]->fd_out.fd, 1) == -1)
					return (FAILURE);
			}
			if (var->cmd[i]->fd_in.fd != 0)
			{
				if (dup2(var->cmd[i]->fd_in.fd, 0) == -1)
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
	else if (frk == 0)
	{
		if (var->cmd[i]->fd_out.fd != 1)
		{
			if (dup2(var->cmd[i]->fd_out.fd, 1) == -1)
				return (FAILURE);
		}
		res = ft_handle_cmd(var, shell, var->cmd[i]);
		if (var->cmd[i]->fd_out.fd != 1)
			close(var->cmd[i]->fd_out.fd);
		return (res);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			return (FAILURE);
		if (pid == 0)
		{
			signal(SIGINT, SIG_IGN);
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
		signal(SIGINT, SIG_IGN);
		if (var->cmd[i + 1]->fd_in.fd != 0)
			close(var->cmd[i + 1]->fd_in.fd);
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

int	ft_single_cmd(t_var *var, t_shell shell)
{
	int	res;

	if (ft_is_cmd(var->cmd[0], var->env) == 0)
		return (FAILURE);
	if (ft_is_builtin_cmd(var->cmd[0]) == 1)
	{
		res = ft_handle_last_cmd(var, shell, 0, 0);
		return (res);
	}
	else
	{
		res = ft_handle_last_cmd(var, shell, 0, 1);
				//if (var->exit_nb == 0)
		return (res);
				//return (FAILURE);
	}
}

int	ft_handle_first_dup(t_var *var)
{
	pid_t	pid;

	if (ft_is_cmd(var->cmd[0], var->env) == 0)
		return (FAILURE);
	pid = fork();
	if (pid == -1)
		return (FAILURE);
	if (pid == 0)
	{
		signal(SIGINT, SIG_IGN);
		if (var->cmd[0]->fd_in.fd != 0)
		{
			if (dup2(var->cmd[0]->fd_in.fd, 0) == -1)
				exit(1);
			exit(0);
		}
		else
			exit(0);
	}
	else
		waitpid(pid, &var->exit_nb, 0);
	return (SUCCESS);
}

// int	ft_handle_ultime_cmd(t_var *var, t_shell shell, int i)
// {
// 	pid_t	pid;

// 	if (ft_is_cmd(var->cmd[i], var->env) == 0)
// 		return (FAILURE);
// 	pid = fork();
// 	if (pid == -1)
// 		return (FAILURE);
// 	if (pid == 0)
// 	{
// 		if (var->cmd[i]->fd_out.fd != 1)
// 		{
// 			if (dup2(var->cmd[i]->fd_out.fd, 1) == -1)
// 				exit(1);
// 			exit(0);
// 		}
		
// 		ft_handle_cmd(var, shell, var->cmd[i]);
// 		exit(0);
// 	}
// 	else
// 	{
// 		waitpid(pid, &var->exit_nb, 0);
// 		if (var->cmd[i]->fd_out.fd != 1)
// 			close(var->cmd[i]->fd_out.fd);
// 	}
// 	return (SUCCESS);
// }

int	ft_handle_pipes(t_var *var, t_shell shell)
{
	int		i;
	pid_t 	pid;

	i = 0;
	if (var->nb_cmd == 1)
		return (ft_single_cmd(var, shell));
	else
	{
		pid = fork();
		if (pid == -1)
			return (FAILURE);
		if (pid == 0)
		{
			signal(SIGINT, SIG_IGN);
			if (var->cmd[0]->fd_in.fd != 0)
				if (dup2(var->cmd[0]->fd_in.fd, 0) == -1)
					return (FAILURE);
			while (i < var->nb_cmd - 1)
			{
				ft_handle_regular_cmd(var, shell, i);
				i++;
			}
			ft_handle_last_cmd(var, shell, i, 2);
			exit(0);
		}
		else
		{
			waitpid(pid, NULL, 0);
			close(var->cmd[i]->fd_out.fd);
		}
		//if (var->exit_nb == 0)
			return (SUCCESS);
		//return (FAILURE);
	}
}

// int	ft_handle_pipes(t_var *var, t_shell shell)
// {
// 	pid_t 	pid;

// 	if (var->nb_cmd == 1)
// 		return (ft_single_cmd(var, shell));
// 	else
// 	{
// 		pid = fork();
// 		if (pid == -1)
// 			return (FAILURE);
// 		if (pid == 0)
// 		{
// 			ft_recursive_pipes(var, shell, var->nb_cmd - 1);
// 			exit(0);
// 		}
// 		else
// 		{
// 			waitpid(pid, NULL, 0);
// 			close(var->cmd[var->nb_cmd - 1]->fd_out.fd);
// 		}
// 		//if (var->exit_nb == 0)
// 			return (SUCCESS);
// 		//return (FAILURE);
// 	}
// }

// int	ft_recursive_pipes(t_var *var, t_shell shell, int i)
// {
// 	pid_t	pid;

// 	if (i > 0)
// 		pid = fork();
// 		if (pid == -1)
// 			return (FAILURE);
// 		if (pid == 0)
// 		{
			
// 			ft_handle_regular_cmd(var, shell, i)
// 		}
// 		else
// 		{
			
// 		}
// 		ft_recursive_pipes(var, shell, i - 1);
	
// 	ft_handle_regular_cmd(var, shell, i);
// }

// if (i == 0 && var->cmd[i]->fd_in.fd != 0)
// 				if (dup2(var->cmd[0]->fd_in.fd, 0) == -1)
// 					return (FAILURE);
