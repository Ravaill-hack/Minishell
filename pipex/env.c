/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:58:25 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/01/06 11:39:16 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	find_line(char *title, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] == title[j])
			j++;
		if (title[j] == '\0' && env[i][j] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*extract_env(char *title, char **env)
{
	int	i;
	int	j;

	i = find_line(title, env);
	j = 0;
	if (i == -1 || !env[i])
		return (NULL);
	while (env[i][j] && env[i][j] != '=')
		j++;
	return (env[i] + j + 1);
}

char	*extract_path(char *cmd, char **env)
{
	int		i;
	char	**raw;
	char	**name_cmd;
	char	*path;

	i = 0;
	raw = ft_split(extract_env("PATH", env), ':');
	name_cmd = ft_split(cmd, ' ');
	while (raw[i])
	{
		path = ft_strjoin3(raw[i], "/", name_cmd[0]);
		if (access(path, F_OK | X_OK) == 0)
		{
			ft_free(raw);
			ft_free(name_cmd);
			return (path);
		}
		if (path)
			free(path);
		i++;
	}
	if (raw)
		ft_free(raw);
	ft_free(name_cmd);
	return (cmd);
}
