/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_build_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:50:54 by julien            #+#    #+#             */
/*   Updated: 2025/03/05 22:38:13 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	**ft_build_cmd_list(t_var *var, t_shell *shell)
{
	t_cmd	**cmd_list;
	int		i;

	i = 0;
	var->nb_cmd = ft_nb_pipes(*(var->token_list)) + 1;
	// ft_putstr_fd("nb cmd : ", 1);
	// ft_putnbr_fd(var->nb_cmd, 1);
	// ft_putchar_fd('\n', 1);
	cmd_list = (t_cmd **)malloc((var->nb_cmd + 1) * sizeof(t_cmd *));
	if (!cmd_list)
		return (NULL);
	while (i < var->nb_cmd)
	{
		cmd_list[i] = ft_create_cmd_node(var, i, shell);
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
