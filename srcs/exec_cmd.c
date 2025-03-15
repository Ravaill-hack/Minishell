/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:14:19 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/15 17:28:34 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE //

#include "minishell.h"

int	ft_check_for_dir(char *path, char *cmd)
{
	struct stat	statbuf;
	
	if ((stat(path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
		|| (cmd[0] == '/' && !cmd[1]))
    {
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(": is a directory.\n", 2);
        return (126);
    }
	return (0);
}

int	ft_try_exec_with_path(char **env, char **split_cmd, char *path, int *status)
{
	int		res;

	res = 0;
	if (access(path, F_OK | X_OK) == 0)
		*status = execve(split_cmd[0], split_cmd, env);
	if (split_cmd[0][0] != '.' && split_cmd[0][1] != '/')
		res = ft_check_for_dir(path, split_cmd[0]);
	if (res != 0 )
		return (res);
	if (*status == -1)
	{
		
		ft_putstr_fd(split_cmd[0], 2);
		if (errno == ENOEXEC)
		{
			ft_putstr_fd(": cannot execute binary file: Exec format error.\n", 2);
			return (127);
		}
		else if (errno == EACCES)
		{
			ft_putstr_fd(": Permission denied.\n", 2);
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
		status = ft_try_exec_with_path(env, split_cmd, path, &status);
		if (status != 0)
			return (free(path), status);
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
