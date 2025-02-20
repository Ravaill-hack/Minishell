/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:01:37 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/20 08:22:30 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_line(t_var var)
{
	/*int	i;

	i = 0;*/
	free(var.line);
	/*while (var.split_line[i])
	{
		free(var.split_line[i]);
		i++;
	}
	free(var.split_line);*/
	return (0);
}

void	ft_free_token_list_until(t_token_list **list, int n)
{
	t_token_list	*current;

	while (n--)
	{
		current = *list;
		*list = (*list)->next;
		free(current);
	}
	free(list);
}

void	ft_clear_and_free_all(t_var var)
{
	if (var.env)
		ft_free_strs(var.env);
	ft_free_line(var);
	rl_clear_history();
	ft_enable_echoctl();
}
