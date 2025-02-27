/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:01:37 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/27 11:02:41 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_clear_and_free_all(t_var var, t_shell shell)
{
	if (var.env)
		ft_free_strs(var.env);
	if (shell.prompt)
		free(shell.prompt);
	rl_clear_history();
	ft_enable_echoctl();
}

void	ft_clear_and_free_while(t_shell shell)
{
	if (shell.prompt)
		free(shell.prompt);
	
	rl_clear_history();
	ft_enable_echoctl();
}