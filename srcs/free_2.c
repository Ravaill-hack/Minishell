/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:12:19 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/28 13:54:45 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_cmd_list(int nb_cmd, t_cmd **list, int imax)
{
	int	i;

	i = 0;
	if (imax == -1)
	{
		ft_putstr_fd("nb_cmd = ", 1);
		ft_putnbr_fd(nb_cmd, 1);
		while (i < (nb_cmd))
		{
			ft_putstr_fd("\ni = ", 1);
			ft_putnbr_fd(i, 1);
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
