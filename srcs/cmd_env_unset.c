/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:44:08 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/10 19:31:12 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE //

#include "minishell.h"

int	ft_cmd_env(char **env, t_cmd *cmd_node)
{
	if (!cmd_node->arg[1])
	{
		ft_print_strs(env);
		return (SUCCESS);
	}
	else
		return (FAILURE);
}

int	ft_cmd_unset(char ***env_ptr, t_cmd *node)
{
	int		line_index;

	if (!node->arg[1])
		return (SUCCESS);
	line_index = ft_get_line_env(*env_ptr, node->arg[1]);
	if (line_index == -1)
		return (SUCCESS);
	else
		return (ft_remove_env_var(env_ptr, line_index));
}
