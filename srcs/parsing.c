/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:00:41 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/16 10:44:32 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_line(t_var *var, char **env)
{
	var->split_line = ft_split(var->line, ' ');
	var->token_list = ft_build_token_list(var->split_line);
}
