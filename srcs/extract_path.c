/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 08:35:01 by julien            #+#    #+#             */
/*   Updated: 2025/03/10 18:45:02 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE // 

#include "minishell.h"

char	*ft_get_path_with_env_path(char *path_raw, char *cmd)
{
	int		i;
	char	**raw;
	char	*path;

	i = 0;
	raw = ft_split(path_raw, ':');
	while (raw[i])
	{
		path = ft_strjoin_n(3, raw[i], "/", cmd);
		if (!path)
			return (ft_free_strs_until(raw, i), NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_free_strs(raw), path);
		if (path)
			free(path);
		i++;
	}
	if (raw)
		ft_free_strs(raw);
	return (NULL);
}

char	*ft_get_path_with_env_pwd(char **env, char *cmd)
{
	char	*path;

	path = ft_strjoin_n(3, ft_extract_env_value_from_key(env, "PWD"), "/", cmd);
	if (!path)
		return (NULL);
	if (access(path, F_OK | X_OK) == 0)
		return (path);
	if (path)
		free(path);
	return (NULL);
}

char	*ft_get_path_without_env(char *cmd)
{
	char	*path;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	path = ft_strjoin_n(3, pwd, "/", cmd);
	if (!path)
		return (NULL);
	if (access(path, F_OK | X_OK) == 0)
		return (path);
	if (path)
		free(path);
	return (NULL);
}

char	*ft_extract_path(char **env, char *cmd)
{
	char	*path_raw;
	char	*path;

	path_raw = ft_extract_env_value_from_key(env, "PATH");
	if (path_raw)
	{
		path = ft_get_path_with_env_path(path_raw, cmd);
		if (!path)
			ft_get_path_with_env_pwd(env, cmd);
	}
	else
		path = ft_get_path_without_env(cmd);
	return (path);
}

char	*ft_sub_path(char *str)
{
	char	*start;
	char	*end;
	char	*path;

	if (!str)
		return (NULL);
	start = str;
	end = ft_strrchr(str, '/');
	if (!end)
		return (NULL);
	path = ft_substr(str, start - str, end - start);
	if (!path)
		return (NULL);
	return (path);
}
