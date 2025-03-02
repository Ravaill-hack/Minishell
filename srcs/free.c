/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:01:37 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/03/02 10:34:15 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_token_list(t_token_list **token_list)
{
	t_token_list	*current;
	t_token_list	*next;

	if (!(*token_list) || !token_list)
		return;
	current = *token_list;
	while (current != NULL)
	{
		next = current->next;
		if (current->val)
			free(current->val);
		free(current);
		current = next;
	}
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

void	ft_clear_and_free_all(t_var *var, t_shell *shell)
{
	if (var->env)
		ft_free_strs(var->env);
	if (shell->prompt)
		free(shell->prompt);
	if (shell)
		free(shell);
	//if (var->token_list)
	//{
	//	ft_putstr_fd("token_list\n", 1);
	//	ft_free_token_list(var->token_list);
	//}
	// if (var.cmd)
	// {
	// 	ft_putstr_fd("cmd_list\n", 1);
	// 	ft_free_cmd_list(var.nb_cmd, var.cmd, -1);
	// }
	rl_clear_history();
	ft_enable_echoctl();
}

void	ft_clear_and_free_while(t_var *var, t_shell *shell)
{
	int	nb_cmd;

	nb_cmd = var->nb_cmd;
	if (shell->prompt)
		free(shell->prompt);
	if (var->token_list)
		ft_free_token_list(var->token_list);
	if (var->cmd)
	 	ft_free_cmd_list(nb_cmd, var->cmd, -1);
}
