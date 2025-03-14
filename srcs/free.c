/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:38:47 by julien            #+#    #+#             */
/*   Updated: 2025/03/14 12:28:32 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE //

#include "minishell.h"

void	ft_free_token_list(t_token_list **token_list)
{
	t_token_list	*current;
	t_token_list	*next;

	if (!token_list)
		return ;
	current = *token_list;
	while (current)
	{
		if (current->val)
			free(current->val);
		next = current->next;
		free(current);
		current = next;
		*token_list = NULL;
	}
}

void	ft_free_token_list_until(t_token_list **list, int n)
{
	t_token_list	*current;

	while (n-- && *list)
	{
		current = *list;
		*list = (*list)->next;
		free(current);
	}
	if (*list)
		*list = NULL;
}

void	ft_clear_and_free_all(t_var *var, t_shell *shell)
{
	if (var->env)
		ft_free_strs(var->env);
	if (shell)
	{
		if (shell->terminal_prompt)
			free(shell->terminal_prompt);
		if (shell->prompt)
			free(shell->prompt);
		free(shell);
	}
	if (var->token_list)
	{
		ft_free_token_list(var->token_list);
		free(var->token_list);
		var->token_list = NULL;
	}
	if (var->fd_pipe)
		ft_free_array2d(var->fd_pipe);
	if (isatty(STDIN_FILENO) && VALGRIND_DEBUG == 0)
		rl_clear_history();
}

void	ft_clear_and_free_all_exit(t_var *var, t_shell *shell)
{
	if (var->env)
		ft_free_strs(var->env);
	if (var->token_list)
	{
		ft_free_token_list(var->token_list);
		free(var->token_list);
		var->token_list = NULL;
	}
	if (shell)
	{
		if (shell->terminal_prompt)
			free(shell->terminal_prompt);
		free(shell);
	}
	if (var->cmd)
		ft_free_cmd_list(var->cmd);
	if (var->fd_pipe)
	{
		//ft_putstr_fd("\nvar fd pipe existe\n", 1);
		ft_free_array2d(var->fd_pipe);
		//if (var->fd_pipe)
			//ft_putstr_fd("\nvar fd pipe existe encore\n", 1);
		//	free (var->fd_pipe);
	}
	if (VALGRIND_DEBUG == 0)
		rl_clear_history();
}

void	ft_clear_and_free_while(t_var *var, t_shell *shell)
{
	if (shell->prompt)
	{
		free(shell->prompt);
		shell->prompt = NULL;
	}
	if (var->token_list)
	{
		ft_free_token_list(var->token_list);
		free(var->token_list);
		var->token_list = NULL;
	}
	// if (var->cmd[0])
	// 	ft_free_strs(var->cmd[0]->arg);
	if (var->cmd)
		ft_free_cmd_list(var->cmd);
	if (var->fd_pipe)
		ft_free_array2d(var->fd_pipe);
}
