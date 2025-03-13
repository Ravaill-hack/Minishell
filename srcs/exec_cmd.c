/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:14:19 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/13 13:17:21 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE //

#include "minishell.h"

int	ft_try_exec_with_path(char **env, char **split_cmd, char *path, int *status)
{
	if (access(path, F_OK | X_OK) == 0)
	{
		*status = execve(split_cmd[0], split_cmd, env);
	}
	if (*status == -1)
	{
		ft_putstr_fd(split_cmd[0], 2);
		if (errno == EISDIR)
		{
			ft_putstr_fd(": is a directory.\n", 2);
			return (126);
		}
		if (errno == EACCES)
		{
			ft_putstr_fd(": permission denied.\n", 2);
			return (126);
		}
		else if (errno == ENOENT)
		{
			ft_putstr_fd(": command not found.\n", 2);
			return (127);
		}
	}
	return (FAILURE);
}

int	ft_exec_cmd(char **env, char **split_cmd)
{
	char	*path;
	int		status;

	status = 0;
	path = ft_sub_path(split_cmd[0]);
	if (path)
	{
		if (ft_try_exec_with_path(env, split_cmd, path, &status) == 127)
			return (127);
	}
	else if (!path)
		path = ft_extract_path(env, split_cmd[0]);
	if (!path)
	{
		ft_putstr_fd(split_cmd[0], 2);
		ft_putstr_fd(": command not found.\n", 2);
		return (127);
	}
	status = execve(path, split_cmd, env);
	free(path);
	if (status == -1)
		return (FAILURE);
	return (SUCCESS);
}
