/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:15:56 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/09 15:16:23 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_valid_key(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]) == 1)
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (ft_strchr("-+*&@#!?:", str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_cmd_export(char ***env_ptr, t_cmd *cmd_node, t_var *var)
{
	int		status;
	int		i;

	status = SUCCESS;
	if (!cmd_node->arg[1])
		status = ft_cmd_export_with_no_args(env_ptr, var);
	else
	{
		i = 1;
		while (cmd_node->arg[i])
		{
			if (ft_is_valid_key(cmd_node->arg[i]) == 1)
			{
				if (ft_cmd_export_with_args(env_ptr, cmd_node->arg[i], var) == FAILURE)
					status = FAILURE;
			}
			else
			{
				ft_putstr_fd("export: '", 2);
				ft_putstr_fd(cmd_node->arg[i], 2);
				ft_putstr_fd("' is not a valid identifier\n", 2);
				status = FAILURE;
			}
			i++;
		}
	}
	return (status);
}

int	ft_cmd_export_with_no_args(char ***env_ptr, t_var *var)
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
	i = 0;
	while (i < ft_strslen(var->declare))
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(var->declare[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (SUCCESS);
}

int	ft_add_to_declare(char *arg, char **env, char ***declare)
{
	int	i;

	i = 0;
	if (ft_get_line_env(env, arg) != -1)
		return (0);
	while ((*declare) && (*declare)[i])
	{
		if ((ft_strncmp(arg, (*declare)[i], ft_strlen(arg)) == 0) && ((*declare)[i][ft_strlen(arg)] == '\0'))
			return (0);
		i++;
	}
	*declare = ft_strsjoinstr(*declare, arg);
	return (0);
}

int	ft_cmd_export_with_args(char ***env_ptr, char *arg, t_var *var)
{
	char	*key;
	char	*value;
	int		line_index;
	int		status;

	if (!ft_strchr(arg, '='))
		return (ft_add_to_declare(arg, var->env, &(var->declare)));
	key = ft_extract_key_env(arg);
	value = ft_extract_value_env(arg);
	if (!key || !*key || !value)
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
	(void)node;
	// if (!node->arg[1])
	// {
		ft_putstr_fd(ft_extract_env_value_from_key(env, "PWD"), 1);
		ft_putchar_fd('\n', 1);
		return (SUCCESS);
	// }
	// return (FAILURE);
}
