/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fill_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:33:05 by julien            #+#    #+#             */
/*   Updated: 2025/03/10 19:08:08 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE // 

#include "minishell.h"

char	*ft_fill_arg_redirs(t_token_list **node)
{
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	str = ft_dup_operand((*node)->type);
	tmp = str;
	(*node) = (*node)->next;
	if (*node && (*node)->val && (*node)->val[0])
		str = ft_strjoin(str, (*node)->val);
	if (tmp != str)
		free(tmp);
	if (*node)
		(*node) = (*node)->next;
	return (str);
}

char	*ft_fill_arg_not_redirs(t_token_list **node)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	str = NULL;
	tmp = NULL;
	while (i == 0 || ft_node_is_not_redir(node))
	{
		tmp = str;
		if (ft_go_to_next_node_condition(node))
			(*node) = (*node)->next;
		if ((*node) && ft_node_is_content(node))
			str = ft_strjoin(str, (*node)->val);
		if (!str && (*node) && (*node)->next)
			(*node) = (*node)->next;
		if (tmp != str)
			free(tmp);
		if ((*node))
			(*node) = (*node)->next;
		i++;
		if (!str && i != 1)
			return (NULL);
	}
	return (str);
}

char	*ft_fill_arg(t_token_list **node)
{
	if ((*node) && (*node)->type < 4)
		return (ft_fill_arg_redirs(node));
	if ((*node) && (*node)->type >= 4)
		return (ft_fill_arg_not_redirs(node));
	return (NULL);
}
