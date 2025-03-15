/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:12:19 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/15 16:46:13 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE //

#include "minishell.h"

t_cmd	*ft_free_cmd_node(t_cmd *node)
{
	if (node->arg)
		node->arg = ft_free_strs(node->arg);
	//if (node->heredoc)
	//	free(node->heredoc);
	if (node)
		free(node);
	return (NULL);
}

t_cmd	**ft_free_cmd_list(t_cmd **cmd)
{
	int	i;

	if (!cmd)
		return (NULL);
	i = 0;
	while (cmd[i])
	{
		cmd[i] = ft_free_cmd_node(cmd[i]);
		i++;
	}
	if (cmd)
		free(cmd);
	return (NULL);
}
