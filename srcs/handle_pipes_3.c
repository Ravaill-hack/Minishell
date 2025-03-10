/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:48:44 by julien            #+#    #+#             */
/*   Updated: 2025/03/10 18:55:20 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE //

#include "minishell.h"

int	ft_is_cmd(t_cmd *cmd, char **env)
{
	char	*path;

	path = NULL;
	if (!cmd->arg[0])
		return (0);
	if (ft_is_builtin_cmd(cmd))
		return (1);
	path = ft_sub_path(cmd->arg[0]);
	if (!path)
		path = ft_extract_path(env, cmd->arg[0]);
	if (!path)
		return (0);
	free(path);
	return (1);
}
