/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:01:37 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/26 08:13:00 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_line(t_var var)
{
	free(var.line);
	return ;
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

void	ft_free_char_array(char **chartab, int imax)
{
	int	i;

	i = 0;
	if (imax == -1)
	{
		while (chartab[i])
		{
			free(chartab[i]);
			i++;
		}
	}
	else
	{
		while (i < imax)
		{
			free(chartab[i]);
			i++;
		}
	}
	free(chartab);
}

void	ft_free_cmd_node(t_cmd *node)
{
	ft_free_char_array(node->arg, -1);
	// A completer en fonction de comment evolue la structure
}

void	ft_free_cmd_list(t_var *var, t_cmd **list, int imax)
{
	int	i;

	i = 0;
	if (imax == -1)
	{
		while (i < (var->nb_cmd))
		{
			ft_free_cmd_node(list[i]);
			i++;
		}
	}
	else
	{
		while (i < imax)
		{
			ft_free_cmd_node(list[i]);
			i++;
		}
	}
	free(list);
}
