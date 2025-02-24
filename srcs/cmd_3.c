/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:06:24 by julien            #+#    #+#             */
/*   Updated: 2025/02/24 13:16:16 by juduchar         ###   ########.fr       */
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
	return (ft_update_env_var_value(&env, pwd_line_index, new_pwd));
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
	return (ft_update_env_var_value(&env, pwd_line_index, new_pwd));
}

int	ft_cmd_skip_name(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] && str[i] == '\"')
	{
		while (str[i] && str[i] != '\"')
			i++;
		i++;
	}
	else if (str[i] && str[i] == '\'')
	{
		while (str[i] && str[i] != '\'')
			i++;
		i++;
	}
	else if (str[i])
	{
		while (str[i] && !ft_isspace(str[i]))
			i++;
	}
	return (i);
}

int	ft_cmd_echo_print_str(char *str, int i, int opt)
{
	// si l'option est a 1 ca veut dire qu'on ne veut pas recopier
	// tous les espaces, sinon on copie tel quel
	if (opt == 1)
	{
		while (str[i])
		{
			while (str[i] && ft_isspace(str[i]))
				i++;
			while (str[i] && !ft_isspace(str[i]))
			{
				ft_putchar_fd(str[i], 1);
				i++;
			}
			if (str[i] != '\0' && ft_isspace(str[i]))
				ft_putchar_fd(' ', 1);
		}
	}
	else
	{
		while (str[i])
		{
			ft_putchar_fd(str[i], 1);
			i++;
		}
	}
	return (SUCCESS);
}
