/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:12:19 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/02 10:04:51 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_cmd_list(int nb_cmd, t_cmd **list, int imax)
{
	(void)list;
	(void)nb_cmd;
	(void)imax;
	/*
	i = 0;
	if (imax == -1)
	{
		while (i < (nb_cmd))
		{
			if (list[i])
				ft_free_strs_until(list[i], -1);
			i++;
		}
	}
	else
	{
		while (i < imax)
		{
			if (list[i])
				ft_free_strs_until(list[i], -1);
			i++;
		}
	}
	//free(list);
	*/
}
