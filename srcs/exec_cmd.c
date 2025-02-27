/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:14:19 by juduchar          #+#    #+#             */
/*   Updated: 2025/02/27 16:04:14 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_extract_path(char **env, char *cmd)
{
	int		i;
	char	**raw;
	char	**name_cmd;
	char	*path;

	i = 0;
	raw = ft_split(ft_extract_env_value_from_key(env, "PATH"), ':');
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
	if (raw)
		ft_free_strs(raw);
	ft_free_strs(name_cmd);
	path = ft_strdup("/bin/bash");
	return (path);
}

char	**ft_set_exec_args(char *path, char **split_cmd)
{
	char	**args;

	if (ft_strncmp(path, "/bin/bash", 9) == 0)
	{
		args = (char **)ft_calloc(4, sizeof(char *));
		if (!args)
			return (NULL);
		args[0] = path;
		args[1] = "-c";
		args[2] = split_cmd[0];
		args[3] = NULL;
	}
	return (args);
}

int	ft_exec_cmd_in_child(char *path, char **split_cmd, char **env)
{
	char	**args;

	if (ft_strncmp(path, "/bin/bash", 9) == 0)
	{
		args = ft_set_exec_args(path, split_cmd);
		execve(path, args, env);
		ft_free_strs(args);
		exit(EXIT_FAILURE);
	}
	else
	{
		execve(path, split_cmd, env);
		exit(EXIT_FAILURE);
	}
	return (FAILURE);
}

int	ft_exec_cmd(char **env, char *cmd)
{
	pid_t	pid;
	char	**split_cmd;
	char	*path;

	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd || !split_cmd[0])
		return (ft_free_strs(split_cmd), FAILURE);
	path = ft_extract_path(env, split_cmd[0]);
	if (!path)
		return (ft_free_strs(split_cmd), FAILURE);
	pid = fork();
	if (pid == -1)
		return (ft_free_strs(split_cmd), free(path), FAILURE);
	if (pid == 0)
		return (ft_exec_cmd_in_child(path, split_cmd, env));
	else
	{
		waitpid(pid, NULL, 0);
		free(path);
		ft_free_strs(split_cmd);
	}
	return (SUCCESS);
}
