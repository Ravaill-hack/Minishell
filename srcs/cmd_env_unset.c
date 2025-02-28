/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:44:08 by juduchar          #+#    #+#             */
/*   Updated: 2025/02/28 11:56:24 by lmatkows         ###   ########.fr       */
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

int	ft_cmd_unset(char ***env_ptr, t_token_list *token_list)
{
	int		line_index;
	char	**split_line;
	int		status;

	split_line = ft_split(token_list->val, ' ');
	if (!split_line[1])
		return (ft_free_strs(split_line), FAILURE);
	line_index = ft_get_line_env(*env_ptr, split_line[1]);
	if (line_index == -1)
		return (ft_free_strs(split_line), FAILURE);
	else
	{
		status = ft_remove_env_var(env_ptr, line_index);
		return (ft_free_strs(split_line), status);
	}
}
