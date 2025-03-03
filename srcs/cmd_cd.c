/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:06:24 by julien            #+#    #+#             */
/*   Updated: 2025/03/03 15:29:31 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_cd(char ***env, t_cmd *node)
{
	int		status;

	if (!node->arg[1])
		status = ft_cmd_cd_home(env);
	else
		status = ft_cmd_cd_path(env, node->arg[1]);
	return (status);
}

int	ft_cmd_cd_home(char ***env)
{
	char	*home;

	if (ft_update_old_pwd(env) == FAILURE)
		return (FAILURE);
	home = ft_extract_env_value_from_key(*env, "HOME");
	if (!home)
		return (FAILURE);
	if (chdir(home) == -1)
	{
		if (errno == EACCES || errno == ENOENT || errno == ENOTDIR)
			perror(NULL);
		return (FAILURE);
	}
	return (ft_update_new_pwd(env, home));
	return (SUCCESS);
}

int	ft_update_old_pwd(char ***env)
{
	char	*old_pwd;

	old_pwd = ft_extract_env_value_from_key(*env, "PWD");
	if (!old_pwd)
		return (FAILURE);
	return (ft_update_env_var_value_from_key(env, "OLDPWD", old_pwd));
}

int	ft_update_new_pwd(char ***env, char *new_pwd)
{
	return (ft_update_env_var_value_from_key(env, "PWD", new_pwd));
}

int	ft_cmd_cd_path(char ***env, char *path)
{
	char	*home;
	char	*old_pwd;
	int		status;
	char	*new_pwd;

	if (ft_update_old_pwd(env) == FAILURE)
		return (FAILURE);
	home = ft_extract_env_value_from_key(*env, "HOME");
	if (!home)
		return (FAILURE);
	old_pwd = ft_extract_env_value_from_key(*env, "PWD");
	if (path[0] == '~')
		path = ft_strjoin_n(3, home, "/", path + 1);
	else
		path = ft_strjoin_n(3, old_pwd, "/", path);
	if (chdir(path) == -1)
	{
		if (errno == EACCES || errno == ENOENT || errno == ENOTDIR)
			perror(NULL);
		return (free(path), FAILURE);
	}
	new_pwd = NULL;
	new_pwd = getcwd(new_pwd, 0);
	status = ft_update_new_pwd(env, new_pwd);
	return (free(path), free(new_pwd), status);
}
