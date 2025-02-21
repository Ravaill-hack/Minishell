/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:26:01 by julien            #+#    #+#             */
/*   Updated: 2025/02/21 17:41:19 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init(t_var *var, char **env)
{
	if (!(isatty(STDIN_FILENO)))
		exit(EXIT_FAILURE);
	var->exit_nb = 0;
	var->env = ft_strsdup(env);
	if (!var->env)
		exit(EXIT_FAILURE);
	var->env = ft_modify_shlvl(var->env, 1);
	if (!var->env)
		exit(EXIT_FAILURE);
	ft_disable_echoctl();
	ft_set_sigquit_reception_handler();
	ft_set_sigint_reception_handler();
}
