/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:35:42 by julien            #+#    #+#             */
/*   Updated: 2025/03/06 17:17:28 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_handle_node_type(t_token_list *node, char *str)
{
	if (node->type == CONTENT || node->type == DOLL)
	{
		if (node->type == DOLL && node->next
			&& (node->print_space_after == 0 && node->next->dq_start == 1))
		{
			str = ft_strjoin(str, node->next->val);
			return (str);
		}
		else if (node->type == DOLL && node->val[0] == '\0')
			return (NULL);
		str = ft_strjoin(str, node->val);
	}
	else if (node->type >= 0 && node->type <= 3)
		str = ft_dup_operand(node->type);
	return (str);
}

char	*ft_fill_arg(t_token_list *node)
{
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	while (node && (node->type != PIPE))
	{
		tmp = str;
		str = ft_handle_node_type(node, str);
		if (tmp != str)
			free(tmp);
		if (!str)
			return (NULL);
		if (node->print_space_after != 0
			|| (node->next
				&& (node->next->type >= 0
					&& node->next->type <= 3)))
			break ;
		node = node->next;
		if (node && node->prev && node->prev->type == DOLL
			&& node->prev->print_space_after == 0 && node->dq_start == 1)
			node = node->next;
	}
	return (str);
}

char	**ft_token_list_to_char_array(t_token_list *node)
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
		array[j] = ft_fill_arg(node);
		node = ft_go_to_next_node(node);
		if (!node)
			break ;
		if (array[j])
			j++;
	}
	array[len] = NULL;
	return (array);
}

t_cmd	*ft_create_cmd_node(t_var *var, int i, t_shell *shell)
{
	t_token_list	*token_node;
	t_cmd			*cmd_node;

	(void) var;
	cmd_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd_node)
		return (NULL);
	cmd_node->heredoc = NULL;
	token_node = ft_go_to_cmd_node(*(var->token_list), i);
	cmd_node->raw = ft_token_list_to_char_array(token_node);
	//ft_putchar_fd('\n', 1);
	if (!cmd_node->raw)
		return (NULL);
	cmd_node->arg = ft_epure_args_array(cmd_node->raw);
	ft_init_fd(cmd_node);
	if (ft_fill_fd(cmd_node, shell) == FAILURE)
		return (NULL);
	// ft_putstr_fd("fd_in : ", 1);
	// ft_putnbr_fd(cmd_node->fd_in.fd, 1);
	// ft_putchar_fd('\n', 1);
	// ft_putstr_fd("fd_out : ", 1);
	// ft_putnbr_fd(cmd_node->fd_out.fd, 1);
	// ft_putchar_fd('\n', 1);
	var->fd_pipe = ft_init_pipes(ft_nb_pipes(*(var->token_list)));
	ft_free_strs_until(cmd_node->raw, -1);
	return (cmd_node);
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
