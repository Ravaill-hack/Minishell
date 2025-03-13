/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:44:08 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/13 21:14:26 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE //

#include "minishell.h"

int	ft_cmd_env(char **env, t_cmd *cmd_node)
{
	char	*path_value;

	if (!cmd_node->arg[1])
	{
		if (ft_get_line_env(env, "PATH") == -1)
		{
			ft_putstr_fd("env: No such file or directory\n", 2);
			return (127);
		}
		path_value = ft_extract_env_value_from_key(env, "PATH");
		if (!path_value[0])
		{
			ft_print_strs(env);
			return (SUCCESS);
		}
		ft_print_strs(env);
		return (SUCCESS);
	}
	else
		return (FAILURE);
}

int	ft_cmd_unset(char ***env_ptr, t_cmd *node)
{
	int		line_index;
	int		i;

	i = 1;
	if (!node->arg[1])
		return (SUCCESS);
	while (node->arg[i])
	{
		line_index = ft_get_line_env(*env_ptr, node->arg[i]);
		if (line_index != -1)
			ft_remove_env_var(env_ptr, line_index);
		i++;
	}
	return (SUCCESS);
}
