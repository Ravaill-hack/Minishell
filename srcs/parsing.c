/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:00:41 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/20 08:44:48 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_line(t_var *var)
{
	var->token_list = ft_parse_token_list(var->line, var->env);
	if (!var->token_list)
		return (ft_free_line(*var), FAILURE);
	return (SUCCESS);
}
