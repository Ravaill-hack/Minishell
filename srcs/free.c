/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:01:37 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/27 18:13:06 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_token_list(t_token_list **token_list)
{
	t_token_list	*current;
	t_token_list	*next;

	current = *token_list;
	while (current != NULL)
	{
		next = current->next;
		if (current->val)
			free(current->val);
		free(current);
		current = next;
	}
	free(token_list);
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

void	ft_free_cmd_node(t_cmd *node)
{
	ft_free_strs_until(node->arg, -1);
}
