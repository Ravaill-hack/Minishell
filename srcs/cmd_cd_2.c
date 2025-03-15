/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:35:50 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/15 17:32:23 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_cmd_cd_get_path(char *raw_path, char *old_pwd)
{
	char	*path;

	if (raw_path[0] != '/')
		path = ft_strjoin_n(3, old_pwd, "/", raw_path);
	else
		path = ft_strdup(raw_path);
	return (path);
}

char	*ft_cmd_cd_get_old_pwd(char **env)
{
	char	*old_pwd;

	old_pwd = ft_extract_env_value_from_key(env, "PWD");
	if (!old_pwd)
		old_pwd = getcwd(NULL, 0);
	return (old_pwd);
}

int	ft_cmd_cd_path(char ***env, char *raw_path)
{
	t_cd	cd;

	cd.old_pwd = ft_cmd_cd_get_old_pwd(*env);
	if (raw_path[0] == '~')
	{
		cd.home = ft_extract_env_value_from_key(*env, "HOME");
		if (!cd.home)
			return (FAILURE);
		cd.path = ft_strjoin_n(3, cd.home, "/", raw_path + 1);
	}
	else
		cd.path = ft_cmd_cd_get_path(raw_path, cd.old_pwd);
	if (chdir(cd.path) == -1)
	{
		if (errno == EACCES || errno == ENOENT || errno == ENOTDIR)
			perror(NULL);
		return (free(cd.path), FAILURE);
	}
	if (ft_update_old_pwd(env) == FAILURE)
		return (FAILURE);
	cd.new_pwd = NULL;
	cd.new_pwd = getcwd(NULL, 0);
	cd.status = ft_update_new_pwd(env, cd.new_pwd);
	free(cd.new_pwd);
	free(cd.path);
	return (cd.status);
}
