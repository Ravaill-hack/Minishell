/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:35:42 by julien            #+#    #+#             */
/*   Updated: 2025/03/07 18:38:01 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//|| ((*node) && (*node)->prev && (*node)->prev->type == DOLL && (!(*node)->prev->val))

char	*ft_fill_arg(t_token_list **node)
{
	char	*str;
	char	*tmp;
	int		i;

	str = NULL;
	tmp = NULL;
	i = 0;
	if ((*node)->type >= 4)
	{
		while (i == 0 || ((*node) && (*node)->type != PIPE && (*node)->prev && (*node)->prev->print_space_after == 0 && (*node)->type >= 4))
		{
			tmp = str;
			if (((*node)->type == DOLL || (*node)->type == CONTENT) && (*node)->val[0] == '$' && !(*node)->val[1]
				&& (*node)->next && (*node)->print_space_after == 0 && ((*node)->next->dq_start == 1 || (*node)->next->sq == 1) && !((*node)->next->type == DOLL && (*node)->next->val[0] == '$' && !(*node)->next->val[1]))
				(*node) = (*node)->next;
			else if ((*node)->type == DOLL && (*node)->val[0] == '$' && !(*node)->val[1] && (*node)->prev && (*node)->prev->dq_start == 0 && (*node)->dq_start == 1 && (*node)->prev->print_space_after == 0 && (*node)->prev->type == DOLL && (*node)->prev->val[0] == '$'  && !(*node)->prev->val[1])	
				(*node) = (*node)->next;
			if ((*node) && ((*node)->type == CONTENT || ((*node)->type == DOLL && (*node)->val)))
				str = ft_strjoin(str, (*node)->val);
			if (!str && (*node) && (*node)->next)	
				(*node) = (*node)->next;
			if (tmp != str)
				free(tmp);
			if ((*node))
				(*node) = (*node)->next;
			i++;
			if (!str && i != 1)
				return (NULL);
		}
		return (str);
	}
	else if ((*node))
	{
		(*node) = (*node)->next;
		return (ft_dup_operand((*node)->type));
	}
	return (NULL);
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
		array[j] = ft_fill_arg(&node);
		if (!node)
		 	break ;
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
