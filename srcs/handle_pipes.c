/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:07:11 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/02 12:53:01 by julien           ###   ########.fr       */
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
