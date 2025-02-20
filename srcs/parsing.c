/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:00:41 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/19 16:07:49 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_line(t_var *var)
{
	//var->split_line = ft_split(var->line, ' ');
	var->token_list = ft_parse_token_list(var->line, var->env);
	if (!var->token_list)
		return (ft_free_line(*var), FAILURE);
	return (SUCCESS);
}
