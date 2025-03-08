/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:06:24 by julien            #+#    #+#             */
/*   Updated: 2025/03/08 17:42:56 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cmd_cd(char ***env, t_cmd *node)
{
	int status;

	if (!node->arg[1])
		status = ft_cmd_cd_home(env);
	else if (node->arg[1][0] == '-' && !node->arg[1][1])
		status = ft_cmd_cd_minus(env);
	else
		status = ft_cmd_cd_path(env, node->arg[1]);
	return (status);
}

int ft_cmd_cd_home(char ***env)
{
	char *home;

	home = ft_strdup(ft_extract_env_value_from_key(*env, "HOME"));
	if (!home)
		return (FAILURE);
	if (chdir(home) == -1)
	{
		if (errno == EACCES || errno == ENOENT || errno == ENOTDIR)
			perror(NULL);
		return (free(home), FAILURE);
	}
	if (ft_update_old_pwd(env) == FAILURE)
		return (free(home), FAILURE);
	if (ft_update_new_pwd(env, home) == FAILURE)
		return (free(home), FAILURE);
	return (free(home), SUCCESS);
}

int ft_cmd_cd_minus(char ***env)
{
	char *tmp_old;
	char *tmp_current;

	tmp_old = ft_strdup(ft_extract_env_value_from_key(*env, "OLDPWD"));
	if (!tmp_old)
		return (FAILURE);
	tmp_current = ft_strdup(ft_extract_env_value_from_key(*env, "PWD"));
	if (!tmp_current)
		return (FAILURE);
	if (chdir(tmp_old) == -1)
	{
		if (errno == EACCES || errno == ENOENT || errno == ENOTDIR)
			perror(NULL);
		return (FAILURE);
	}
	if (ft_update_env_var_value_from_key(env, "OLDPWD", tmp_current) == FAILURE)
		return (free(tmp_old), free(tmp_current), FAILURE);
	if (ft_update_env_var_value_from_key(env, "PWD", tmp_old) == FAILURE)
		return (free(tmp_old), free(tmp_current), FAILURE);
	ft_putstr_fd(tmp_old, 1);
	ft_putchar_fd('\n', 1);
	return (free(tmp_old), free(tmp_current), SUCCESS);
}

int ft_update_old_pwd(char ***env)
{
	char *old_pwd;

	old_pwd = ft_extract_env_value_from_key(*env, "PWD");
	if (!old_pwd)
		return (FAILURE);
	return (ft_update_env_var_value_from_key(env, "OLDPWD", old_pwd));
}

int ft_update_new_pwd(char ***env, char *new_pwd)
{
	return (ft_update_env_var_value_from_key(env, "PWD", new_pwd));
}

int ft_cmd_cd_path(char ***env, char *path)
{
	char *home;
	char *old_pwd;
	int status;
	char *new_pwd;

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
	if (ft_update_old_pwd(env) == FAILURE)
		return (FAILURE);
	new_pwd = NULL;
	new_pwd = getcwd(new_pwd, 0);
	status = ft_update_new_pwd(env, new_pwd);
	return (free(path), free(new_pwd), status);
}
