/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:14:19 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/09 00:11:21 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_extract_path(char **env, char *cmd)
{
	int		i;
	char	*path_raw;
	char	**raw;
	char	**name_cmd;
	char	*path;
	char	*path_default;

	i = 0;
	path_raw = ft_extract_env_value_from_key(env, "PATH");
	if (path_raw)
	{
		raw = ft_split(path_raw, ':');
		name_cmd = ft_split(cmd, ' ');
		while (raw[i])
		{
			path = ft_strjoin_n(3, raw[i], "/", name_cmd[0]);
			if (!path)
				return (NULL);
			if (access(path, F_OK | X_OK) == 0)
				return (ft_free_strs(raw), ft_free_strs(name_cmd), path);
			if (path)
				free(path);
			i++;
		}
		path = ft_strjoin_n(3, ft_extract_env_value_from_key(env, "PWD"), "/", name_cmd[0]);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_free_strs(raw), ft_free_strs(name_cmd), path);
		if (path)
			free(path);		
		if (raw)
			ft_free_strs(raw);
		ft_free_strs(name_cmd);
		return (NULL);
	}
	else
	{
		path_default = NULL;
		getcwd(path_default, 0);
		name_cmd = ft_split(cmd, ' ');
		path = ft_strjoin_n(3, path_default, "/", name_cmd[0]);
		ft_putstr_fd(path, 1);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_free_strs(name_cmd), path);
		if (path)
			free(path);
		ft_free_strs(name_cmd);
	}
	return (NULL);
}

char *ft_sub_path(char *str)
{
	char	*start;
	char	*end;
	char	*path;

	start = str;
	end = ft_strrchr(str, '/');
	if (!end)
		return (NULL);
	path = ft_substr(str, start - str, end - start);
	if (!path)
		return (NULL);
	return (path);
}

int	ft_exec_cmd(char **env, char **split_cmd)
{
	char	*path;
	int		status;

	status = 0;
	path = ft_sub_path(split_cmd[0]);
	if (path)
	{
		if (access(path, F_OK | X_OK) == 0)
			status = execve(split_cmd[0], split_cmd, env);
		free(path);
		return (FAILURE);
	}
	else if (!path)
		path = ft_extract_path(env, split_cmd[0]);
	if (!path)
		return (FAILURE);
	status = execve(path, split_cmd, env);
	//ft_exec_error(split_cmd);
	free(path);
	if (status == -1)
		return (FAILURE);
	return (SUCCESS);
}
