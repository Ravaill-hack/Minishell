/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:35:42 by julien            #+#    #+#             */
/*   Updated: 2025/03/12 14:33:15 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE // 

#include "minishell.h"

int	*ft_init_redir_check(t_token_list *node)
{
	int	len;
	int	*check_tab;
	int	i;

	len = ft_nb_str(node);
	check_tab = (int *)malloc((len) * sizeof(int));
	if (!check_tab)
		return (NULL);
	i = 0;
	while (i < len)
	{
		check_tab[i] = 0;
		i++;
	}
	return (check_tab);
}

char	**ft_token_list_to_char_array(t_token_list *node, t_cmd **cmd_node)
{
	char	**array;
	int		len;
	int		j;

	len = ft_nb_str(node);
	j = 0;
	array = (char **)malloc((len + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (j < len)
	{
		if (node->type <= 3)
			(*cmd_node)->is_redir[j] = 1;
		array[j] = ft_fill_arg(&node);
		if (!node)
			break ;
		j++;
	}
	array[len] = NULL;
	return (array);
}

t_cmd	*ft_create_cmd_node(t_var *var, int i)
{
	t_token_list	*token_node;
	t_cmd			*cmd_node;

	(void) var;
	cmd_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd_node)
		return (NULL);
	cmd_node->heredoc = NULL;
	token_node = ft_go_to_cmd_node(*(var->token_list), i);
	cmd_node->is_redir = ft_init_redir_check(token_node);
	cmd_node->raw = ft_token_list_to_char_array(token_node, &cmd_node);
	if (!cmd_node->raw)
		return (NULL);
	cmd_node->arg = ft_epure_args_array(cmd_node->raw, cmd_node->is_redir);
	ft_init_fd(cmd_node);
	if (ft_fill_fd(cmd_node, var) == FAILURE)
		return (NULL);
	var->fd_pipe = ft_init_pipes(ft_nb_pipes(*(var->token_list)));
	ft_free_strs_until(cmd_node->raw, -1);
	// if (cmd_node->raw)
	// 	free(cmd_node->raw);
	if (cmd_node->is_redir)
		free(cmd_node->is_redir);
	return (cmd_node);
}

t_cmd	**ft_build_cmd_list(t_var *var)
{
	t_cmd	**cmd_list;
	int		i;

	i = 0;
	var->nb_cmd = ft_nb_pipes(*(var->token_list)) + 1;
	cmd_list = (t_cmd **)malloc((var->nb_cmd + 1) * sizeof(t_cmd *));
	if (!cmd_list)
		return (NULL);
	while (i < var->nb_cmd)
	{
		cmd_list[i] = ft_create_cmd_node(var, i);
		if (!cmd_list[i] && i == 0)
			return (NULL);
		if (!cmd_list[i] && i != 0)
			return (ft_free_cmd_list_until(cmd_list, i));
		else if (!cmd_list[i] && i == 0)
			return (NULL);
		i++;
	}
	cmd_list[i] = NULL;
	ft_set_pipes(cmd_list, var->nb_cmd, var->fd_pipe);
	return (cmd_list);
}

t_cmd	**ft_free_cmd_list_until(t_cmd **cmd_list, int n)
{
	int	i;

	i = 0;
	if (n == -1)
	{
		while (cmd_list[i])
		{
			free(cmd_list[i]);
			i++;
		}
	}
	else
	{
		while (i < n)
		{
			free(cmd_list[i]);
			i++;
		}
	}
	if (cmd_list)
		free(cmd_list);
	return (NULL);
}
