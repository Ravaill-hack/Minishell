/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:44:08 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/12 09:53:55 by Lmatkows         ###   ########.fr       */
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
