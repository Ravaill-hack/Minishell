/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:54:47 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/28 14:01:33 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_fill_arg(t_token_list *node)
{
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	while (node && (node->type != PIPE))
	{
		tmp = str;
		if (node->type == CONTENT || node->type == DOLL)
		{
			if (node->type == DOLL && node->val[0] == '\0')
				return (NULL);
			str = ft_strjoin(str, node->val);
		}
		else if (node->type >= 0 && node->type <= 3)
			str = ft_dup_operand(node->type);
		if (tmp != str)
			free (tmp);
		if (!str)
			return (NULL);
		if (node->print_space_after != 0)
			break ;
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
		if (array[j])
			j++;
	}
	array[j] = NULL;
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
	token_node = ft_go_to_cmd_node(*(var->token_list), i);
	cmd_node->raw = ft_token_list_to_char_array(token_node);
	if (!cmd_node->raw)
		return (NULL);
	cmd_node->arg = ft_epure_args_array(cmd_node->raw);
	ft_init_fd(cmd_node);
	ft_fill_fd(cmd_node);
	ft_free_strs_until(cmd_node->raw, -1);
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
		if (!cmd_list[i])
			return (ft_free_cmd_list(var->nb_cmd, cmd_list, i), NULL);
		i++;
	}
	cmd_list[i] = NULL;
	return (cmd_list);
}
