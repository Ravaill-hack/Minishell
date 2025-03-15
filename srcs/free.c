/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:38:47 by julien            #+#    #+#             */
/*   Updated: 2025/03/15 16:52:20 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE //

#include "minishell.h"

t_token_list	**ft_free_token_list(t_token_list **token_list)
{
	t_token_list	*current;
	t_token_list	*next;

	if (!token_list || !*token_list)
		return (NULL);
	current = *token_list;
	while (current)
	{
		if (current->val)
		{
			free(current->val);
			current->val = NULL;
		}
		next = current->next;
		free(current);
		current = next;
	}
	if (*token_list)
		*token_list = NULL;
	if (token_list)
		free(token_list);
	return (NULL);
}

t_token_list	**ft_free_token_list_until(t_token_list **list, int n)
{
	t_token_list	*current;

	while (n-- && *list)
	{
		current = *list;
		*list = (*list)->next;
		free(current);
		current = NULL;
	}
	if (*list)
		*list = NULL;
	if (list)
		free(list);
	return (NULL);
}

void	ft_clear_and_free_all(t_var *var, t_shell **shell)
{
	if (var->env)
		ft_free_strs(var->env);
	if (*shell)
	{
		ft_check_and_free((void **)(&((*shell)->tp)));
		ft_check_and_free((void **)(&((*shell)->prompt)));
		(*shell) = ft_check_and_free((void **)shell);
	}
	if (var->token_list)
		var->token_list = ft_free_token_list(var->token_list);
	if (isatty(STDIN_FILENO) && VALGRIND_DEBUG == 0)
		rl_clear_history();
}

void	ft_clear_and_free_all_exit(t_var *var, t_shell **shell)
{
	if (var->env)
		var->env = ft_free_strs(var->env);
	if (var->token_list)
		var->token_list = ft_free_token_list(var->token_list);
	if (*shell)
	{
		ft_check_and_free((void **)(&((*shell)->tp)));
		ft_check_and_free((void **)(&((*shell)->prompt)));
		(*shell) = ft_check_and_free((void **)shell);
	}
	if (var->cmd)
	 	var->cmd = ft_free_cmd_list(var->cmd);
	if (VALGRIND_DEBUG == 0)
		rl_clear_history();
}

void	ft_clear_and_free_while(t_var *var, t_shell **shell)
{
	if (*shell)
		ft_check_and_free((void **)(&((*shell)->prompt)));
	if (var->token_list)
		var->token_list = ft_free_token_list(var->token_list);
	// if (var->cmd[0])
	// 	ft_free_strs(var->cmd[0]->arg);
	if (var->cmd)
		var->cmd = ft_free_cmd_list(var->cmd);
}
