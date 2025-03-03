/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:14:19 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/03 10:34:51 by lmatkows         ###   ########.fr       */
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
	return (NULL);
}

char	**ft_set_exec_args(char *path, char **split_cmd)
{
	char	**args;

	args = (char **)ft_calloc(4, sizeof(char *));
	if (!args)
		return (NULL);
	args[0] = path;
	args[1] = "-c";
	args[2] = split_cmd[0];
	args[3] = NULL;
	return (args);
}

int	ft_exec_cmd(char **env, char **split_cmd)
{
	char	*path;
	int		status;
	char	**args;

	status = 0;
	path = ft_extract_path(env, split_cmd[0]);
	ft_putstr_fd(path, 1);
	ft_putchar_fd('\n', 1);
	if (!path)
		return (FAILURE);
	args = ft_set_exec_args(path, split_cmd);
	if (!args)
		return (FAILURE);
	status = execve(path, args, env);
	if (status == -1)
		ft_putstr_fd("echec\n", 1);
	printf("%s\n", strerror(errno));
	ft_free_strs(args);
	free(path);
	if (status == -1)
		return (FAILURE);
	return (SUCCESS);
}
