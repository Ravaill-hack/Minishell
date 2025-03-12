/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:12:19 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/12 13:32:39 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE //

#include "minishell.h"

void	ft_free_cmd_node(t_cmd *node)
{
	//if (node->arg)
	//	ft_free_strs(node->arg);
	//if (node->raw)
	//	ft_free_strs(node->arg);
	//if (node->chev)
	//	ft_free_strs(node->chev);
	if (node->heredoc)
		free(node->heredoc);
	if (node)
		free(node);
}

void	ft_free_cmd_list(t_cmd **cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = 0;
	while (cmd[i])
	{
		ft_free_cmd_node(cmd[i]);
		i++;
	}
	free(cmd);
}
