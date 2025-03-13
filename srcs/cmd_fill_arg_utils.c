/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fill_arg_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:31:13 by julien            #+#    #+#             */
/*   Updated: 2025/03/13 16:26:54 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE // 

#include "minishell.h"

int	ft_node_is_doll(t_token_list *node)
{
	return (node->val[0] == '$' && !node->val[1]);
}

int	ft_go_to_next_node_condition(t_token_list **node)
{
	if ((*node) && ((*node)->type == DOLL || (*node)->type == CONTENT))
	{
		if (ft_node_is_doll(*node)
			&& (*node)->print_space_after == 0
			&& (*node)->next
			&& ((*node)->next->dq_start == 1 || (*node)->next->sq == 1)
			&& !((*node)->next->type == DOLL)
			&& (ft_node_is_doll((*node)->next)))
			return (1);
	}
	else if ((*node) && ((*node)->type == DOLL))
	{
		if (ft_node_is_doll(*node)
			&& (*node)->dq_start == 1
			&& (*node)->prev
			&& (*node)->prev->type == DOLL
			&& (*node)->prev->dq_start == 0
			&& (*node)->prev->print_space_after == 0
			&& (ft_node_is_doll((*node)->prev)))
			return (1);
	}
	return (0);
}

int	ft_node_is_not_redir(t_token_list **node)
{
	return ((*node) && (*node)->type > 4
		&& (*node)->prev && (*node)->prev->print_space_after == 0);
}

int	ft_node_is_content(t_token_list **node)
{
	int	cond;
	cond = ((*node)->type == 6 || ((*node)->type == 7 && (*node)->val));
	if (*node && (*node)->prev && ((*node)->prev->type == 6
		|| (*node)->prev->type == 7) && (*node)->prev->val
		&& (*node)->prev->val[0] == '$' && !(*node)->prev->val[1]
		&& (*node)->prev->sq == 0 && (*node)->prev->dq_start == 0
		&& (*node)->prev->print_space_after == 0 && (*node)->dq_start == 1)
		return (0);
	return (cond);
}
