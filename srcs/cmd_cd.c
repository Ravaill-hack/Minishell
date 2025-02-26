/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:06:24 by julien            #+#    #+#             */
/*   Updated: 2025/02/26 14:45:34 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_cd(char ***env, t_token_list *token_list)
{
	char	**split_line;
	int		status;

	split_line = ft_split(token_list->val, ' ');
	if (!split_line[1])
		status = ft_cmd_cd_home(env);
	else
		status = ft_cmd_cd_path(env, split_line[1]);
	return (ft_free_strs(split_line), status);
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
	char	*old_pwd;
	int		status;

	if (ft_update_old_pwd(env) == FAILURE)
		return (FAILURE);
	old_pwd = ft_extract_env_value_from_key(*env, "PWD");
	path = ft_strjoin_n(3, old_pwd, "/", path);
	if (chdir(path) == -1)
	{
		if (errno == EACCES || errno == ENOENT || errno == ENOTDIR)
			perror(NULL);
		free(path);
		return (FAILURE);
	}
	status = ft_update_new_pwd(env, path);
	free(path);
	return (status);
}
