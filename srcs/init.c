/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:26:01 by julien            #+#    #+#             */
/*   Updated: 2025/02/24 12:00:55 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init(t_var *var, char **env)
{
	int	shlvl;
	
	if (!(isatty(STDIN_FILENO)))
		exit(EXIT_FAILURE);
	var->exit_nb = 0;
	var->env = ft_strsdup(env);
	if (!var->env)
		exit(EXIT_FAILURE);
	shlvl = ft_atoi(getenv("SHLVL"));
	if (ft_update_env_var_value(&(var->env), ft_get_line_env(var->env, "SHLVL"), ft_itoa(shlvl + 1)) == FAILURE)
		exit(EXIT_FAILURE);
	if (!var->env)
		exit(EXIT_FAILURE);
	ft_disable_echoctl();
	ft_set_sigquit_reception_handler();
	ft_set_sigint_reception_handler();
}
