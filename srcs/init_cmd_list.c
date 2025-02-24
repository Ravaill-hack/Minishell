/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:31:57 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/24 15:28:04 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int	ft_args_array_len(t_token_list *node)
{
	int	len;
	int	i;

	len = 0;
	i = ft_cmd_skip_name(node->val);
	while (node && (node->type == CONTENT || node->type == DOLL))
	{
		if (node->type == DOLL)
			len++;
		else
		{

		}
		node = node->next;
	}
}

char	**ft_token_list_to_char_array(t_token_list *node)
{
	
}


t_cmd	**ft_build_cmd_list(t_var *var)
{
	t_cmd	**cmd_list;
	int		len;

	len = ft_nb_pipes(var->token_list) + 1;
	cmd_list = (t_cmd **)malloc((len + 1) * sizeof(t_cmd *));
	if(!cmd_list)
		return (NULL);
}
*/
