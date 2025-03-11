/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:15:56 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/11 11:01:13 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (ft_is_valid_key(cmd_node->arg[i]) == 1
				&& cmd_node->arg[i][0] != '=')
			{
				if (ft_cmd_export_with_args(env_ptr,
						cmd_node->arg[i], var) == FAILURE)
					status = FAILURE;
			}
			else
				status = ft_cmd_export_invalid_id(cmd_node->arg, i);
			i++;
		}
	}
	return (status);
}

int	ft_cmd_export_invalid_id(char **args, int i)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(args[i], 2);
	ft_putstr_fd("' is not a valid identifier\n", 2);
	return (FAILURE);
}

int	ft_cmd_export_with_no_args(char ***env_ptr, t_var *var)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strslen(*env_ptr);
	while (i < len)
	{
		ft_cmd_export_print_declare(*env_ptr, i);
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

int	ft_cmd_pwd(char **env)
{
	ft_putstr_fd(ft_extract_env_value_from_key(env, "PWD"), 1);
	ft_putchar_fd('\n', 1);
	return (SUCCESS);
}
