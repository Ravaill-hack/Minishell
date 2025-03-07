/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:15:56 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/07 10:25:39 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_export(char ***env_ptr, char **split_line)
{
	int		status;

	if (!split_line[1])
		status = ft_cmd_export_with_no_args(env_ptr);
	else
		status = ft_cmd_export_with_args(env_ptr, split_line[1]);
	return (status);
}

int	ft_cmd_export_with_no_args(char ***env_ptr)
{
	size_t	i;
	size_t	len;
	char	*key;
	char	*value;

	i = 0;
	len = ft_strslen(*env_ptr);
	while (i < len)
	{
		ft_putstr_fd("declare -x ", 1);
		key = ft_extract_key_env((*env_ptr)[i]);
		ft_putstr_fd(key, 1);
		free(key);
		ft_putchar_fd('=', 1);
		ft_putchar_fd('"', 1);
		value = ft_extract_value_env((*env_ptr)[i]);
		ft_putstr_fd(value, 1);
		free(value);
		ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (SUCCESS);
}

int	ft_cmd_export_with_args(char ***env_ptr, char *arg)
{
	char	*key;
	char	*value;
	int		line_index;
	int		status;

	key = ft_extract_key_env(arg);
	value = ft_extract_value_env(arg);
	if (!key || !*key || !value || !*value)
		return (FAILURE);
	line_index = ft_get_line_env(*env_ptr, key);
	free(key);
	if (line_index == -1)
		status = ft_add_env_var(env_ptr, arg);
	else
		status = ft_update_env_var_value(env_ptr, line_index, value);
	free(value);
	return (status);
}

int	ft_cmd_pwd(char **env, t_cmd *node)
{
	if (!node->arg[1])
	{
		printf("%s\n", ft_extract_env_value_from_key(env, "PWD"));
		return (SUCCESS);
	}
	return (FAILURE);
}
