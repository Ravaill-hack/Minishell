/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:00:41 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/18 14:35:00 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_line(t_var *var)
{
	var->split_line = ft_split(var->line, ' ');
	var->token_list = ft_build_token_list(var->split_line);
	if (!var->token_list)
		return (ft_free_line(*var), FAILURE);
	return (SUCCESS);
}
