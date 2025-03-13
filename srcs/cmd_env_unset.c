/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:44:08 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/13 19:40:47 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE //

#include "minishell.h"

int	ft_cmd_env(char **env, t_cmd *cmd_node)
{
	char	*path;

	if (!cmd_node->arg[1])
	{
		path = ft_extract_env_value_from_key(env, "PATH");
		if (!path)
		{
			ft_putstr_fd("env: No such file or directory\n", 2);
			return (127);
		}
		ft_print_strs(env);
		free(path);
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
