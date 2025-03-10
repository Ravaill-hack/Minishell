/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:09:21 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/10 19:23:53 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE //

#include "minishell.h"

int	ft_nb_pipes(t_token_list *list)
{
	int	res;

	res = 0;
	while (list)
	{
		if (list->type == PIPE)
			res ++;
		list = list->next;
	}
	return (res);
}

int	ft_nb_dolls(t_token_list *list)
{
	int	res;

	res = 0;
	while (list)
	{
		if (list->type == DOLL)
			res ++;
		list = list->next;
	}
	return (res);
}

int	ft_nb_str(t_token_list *list)
{
	int	res;

	res = 0;
	while (list && (list->type != PIPE))
	{
		if ((list->print_space_after == 1)
			|| (list->next && list->next->type == PIPE)
			|| !(list->next)
			|| (list->next->type >= 0 && list->next->type <= 3))
			res ++;
		list = list->next;
	}
	return (res);
}
