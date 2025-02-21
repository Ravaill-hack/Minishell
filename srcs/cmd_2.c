/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:15:56 by juduchar          #+#    #+#             */
/*   Updated: 2025/02/21 15:50:21 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_cd(char **env, t_token_list *token_list)
{
	char	**split_line;
	char	*path;
	char	*old_pwd;
	char	*new_pwd;
	int		pwd_line_index;

	split_line = ft_split(token_list->val, ' ');
	if (!split_line[1])
	{
		path = extract_env_value_from_key(env, "HOME");
		if (!path)
			return (FAILURE);
		exec_cmd(env, ft_strjoin("cd ", path));
		new_pwd = path;
		pwd_line_index = ft_get_line_env(env, "PWD");
		if (ft_update_env_var_value(&env, pwd_line_index, new_pwd) == FAILURE)
			return (FAILURE);
		return (SUCCESS);
	}
	else
	{
		path = split_line[1];
		old_pwd = extract_env_value_from_key(env, "PWD");
		if (!old_pwd)
			return (FAILURE);
		path = ft_strjoin(old_pwd, path);
		if (exec_cmd(env, ft_strjoin("cd ", path)) == FAILURE)
			return (FAILURE);
		new_pwd = path;
		pwd_line_index = ft_get_line_env(env, "PWD");
		if (ft_update_env_var_value(&env, pwd_line_index, new_pwd) == FAILURE)
			return (FAILURE);
		return (SUCCESS);
	}
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
