/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:44:08 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/03 16:13:47 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (FAILURE);
	line_index = ft_get_line_env(*env_ptr, node->arg[1]);
	if (line_index == -1)
	{
		ft_putstr_fd("on est ici\n", 1);
		return (FAILURE);
	}
	else
	{
		ft_putstr_fd("on est la\n", 1);
		return(ft_remove_env_var(env_ptr, line_index));
	}
}
