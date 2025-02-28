/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:12:19 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/28 10:36:25 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_cmd_list(t_var var, t_cmd **list, int imax)
{
	int	i;

	i = 0;
	if (imax == -1)
	{
		while (i < (var.nb_cmd))
		{
			if (list[i])
				ft_free_cmd_node(list[i]);
			i++;
		}
	}
	else
	{
		while (i < imax)
		{
			if (list[i])
				ft_free_cmd_node(list[i]);
			i++;
		}
	}
	//free(list);
}
