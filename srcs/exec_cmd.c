/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:14:19 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/04 17:53:48 by lmatkows         ###   ########.fr       */
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

int	ft_exec_cmd(char **env, char **split_cmd)
{
	char	*path;
	int		status;

	status = 0;
	path = ft_extract_path(env, split_cmd[0]);
	if (!path)
		return (FAILURE);
	ft_putstr_fd("jarrive jusque ici\n", 1);
	status = execve(path, split_cmd, env);
	ft_putstr_fd("mais pas jusque la\n", 1);
	if (status == -1)
		ft_putstr_fd("echec\n", 1);
	printf("%s\n", strerror(errno));
	free(path);
	if (status == -1)
		return (FAILURE);
	return (SUCCESS);
}
