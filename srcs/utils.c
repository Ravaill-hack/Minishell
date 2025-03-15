/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:09:21 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/15 10:56:55 by lmatkows         ###   ########.fr       */
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
		if ((list->psa == 1)
			|| (list->next && list->next->type == PIPE)
			|| !(list->next)
			|| (list->next->type >= 0 && list->next->type <= 3))
			res ++;
		list = list->next;
	}
	return (res);
}

void	ft_set_pipes_needs(t_cmd **cmd, int nb_cmd)
{
	int	i;

	i = 0;
	while (i < nb_cmd)
	{
		cmd[i]->need_pipe_in = ft_need_to_grep_from_pipe(cmd, i);
		cmd[i]->need_pipe_out = ft_need_to_send_in_pipe(cmd, i, nb_cmd);
		i++;
	}
}
