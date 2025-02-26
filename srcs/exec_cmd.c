/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:14:19 by juduchar          #+#    #+#             */
/*   Updated: 2025/02/26 10:55:31 by juduchar         ###   ########.fr       */
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
		path = ft_strjoin3(raw[i], "/", name_cmd[0]);
		if (access(path, F_OK | X_OK) == 0)
		{
			ft_free_strs(raw);
			ft_free_strs(name_cmd);
			return (path);
		}
		if (path)
			free(path);
		i++;
	}
	if (raw)
		ft_free_strs(raw);
	ft_free_strs(name_cmd);
	return ("/bin/bash");
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
	else
		args = split_cmd;
	return (args);
}

void	ft_handle_pid(pid_t pid, char *path, char **args, char **env)
{
	int	status;

	if (pid == 0)
	{
		execve(path, args, env);
		exit(127);
	}
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		printf("OK");
}

int	ft_exec_cmd(char **env, char *cmd)
{
	pid_t	pid;
	char	**split_cmd;
	char	*path;
	char	**args;

	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd || !split_cmd[0])
		return (ft_free_strs(split_cmd), FAILURE);
	path = ft_extract_path(env, split_cmd[0]);
	if (!path)
		return (ft_free_strs(split_cmd), FAILURE);
	args = ft_set_exec_args(path, split_cmd);
	if (!args)
		return (ft_free_strs(split_cmd), free(path), FAILURE);
	pid = fork();
	if (pid == -1)
		return (ft_free_strs(args),
			ft_free_strs(split_cmd), free(path), FAILURE);
	ft_handle_pid(pid, path, args, env);
	if (args != split_cmd)
		ft_free_strs(args);
	ft_free_strs(split_cmd);
	free(path);
	return (SUCCESS);
}
