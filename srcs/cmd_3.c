/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:06:24 by julien            #+#    #+#             */
/*   Updated: 2025/02/22 16:15:29 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_cd(char **env, t_token_list *token_list)
{
	char	**split_line;

	split_line = ft_split(token_list->val, ' ');
	if (!split_line[1])
		return (ft_cmd_cd_home(env));
	else
		return (ft_cmd_cd_path(env, split_line[1]));
}

int	ft_cmd_cd_home(char **env)
{
	char	*home;
	char	*new_pwd;
	int		pwd_line_index;

	home = ft_extract_env_value_from_key(env, "HOME");
	if (!home)
		return (FAILURE);
	ft_exec_cmd(env, ft_strjoin("cd ", home));
	new_pwd = home;
	pwd_line_index = ft_get_line_env(env, "PWD");
	if (ft_update_env_var_value(&env, pwd_line_index, new_pwd) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	ft_cmd_cd_path(char **env, char *path)
{
	char	*old_pwd;
	char	*new_pwd;
	int		pwd_line_index;

	old_pwd = ft_extract_env_value_from_key(env, "PWD");
	if (!old_pwd)
		return (FAILURE);
	path = ft_strjoin(old_pwd, path);
	if (ft_exec_cmd(env, ft_strjoin("cd ", path)) == FAILURE)
		return (FAILURE);
	new_pwd = path;
	pwd_line_index = ft_get_line_env(env, "PWD");
	if (ft_update_env_var_value(&env, pwd_line_index, new_pwd) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	ft_cmd_echo(t_token_list *token_list)
{
	char	**split_line;
	size_t	i;

	split_line = ft_split(token_list->val, ' ');
	if (split_line[1])
	{
		if (ft_strncmp(split_line[1], "-n", 2) == 0)
			i = 2;
		else
			i = 1;
		while (split_line[i])
		{
			printf("%s", split_line[i]);
			if (split_line[i + 1])
				printf(" ");
			i++;
		}
		if (ft_strncmp(split_line[1], "-n", 2) != 0)
			printf("\n");
	}
	return (SUCCESS);
}
