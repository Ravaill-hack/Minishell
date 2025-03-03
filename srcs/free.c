/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:01:37 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/03/03 19:14:25 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_token_list(t_token_list **token_list)
{
	t_token_list	*current;
	t_token_list	*next;

	if (!token_list || !(*token_list))
		return ;
	current = *token_list;
	while (current)
	{
		if (current->val)
			free(current->val);
		next = current->next;
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
	*list = NULL;
}

void	ft_clear_and_free_all(t_var *var, t_shell *shell)
{
	if (var->env)
		ft_free_strs(var->env);
	if (shell)
		free(shell);
	if (VALGRIND_DEBUG == 0)
		rl_clear_history();
	ft_enable_echoctl();
}

#include <stdio.h>
void	ft_clear_and_free_while(t_var *var, t_shell *shell)
{
	if (shell->prompt)
		free(shell->prompt);
	if (var->token_list)
		ft_free_token_list(var->token_list);
	if (var->cmd[0])
		ft_free_strs(var->cmd[0]->arg);
	if (var->cmd)
		ft_free_cmd_list(var->cmd);
	if (var->fd_pipe)
		ft_free_array2d(var->fd_pipe);
}
