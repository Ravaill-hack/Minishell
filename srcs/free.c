/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:01:37 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/27 19:03:17 by lmatkows         ###   ########.fr       */
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
	ft_putstr_fd("1\n", 1);
	if (var->env)
	{
		ft_putstr_fd("env\n", 1);
		ft_free_strs(var->env);
	}
	if (shell->prompt)
	{
		ft_putstr_fd("prompt\n", 1);
		free(shell->prompt);
	}
	if (shell)
	{
		ft_putstr_fd("shell\n", 1);
		free(shell);
	}
	//if (var->token_list)
	//{
	//	ft_putstr_fd("token_list\n", 1);
	//	ft_free_token_list(var->token_list);
	//}
	if (var->cmd)
	{
		ft_putstr_fd("cmd_list\n", 1);
		ft_free_cmd_list(var, var->cmd, -1);
	}
	rl_clear_history();
	ft_enable_echoctl();
}

void	ft_clear_and_free_while(t_shell shell, t_var *var)
{
	ft_putstr_fd("0\n", 1);
	if (shell.prompt)
		free(shell.prompt);
	rl_clear_history();
	ft_enable_echoctl();
	if (var->token_list)
		ft_free_token_list(var->token_list);
	if (var->cmd)
		ft_free_cmd_list(var, var->cmd, -1);
}

void	ft_free_cmd_node(t_cmd *node)
{
	ft_free_strs_until(node->arg, -1);
}
