/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:26:01 by julien            #+#    #+#             */
/*   Updated: 2025/02/24 17:04:34 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init(t_var *var, char **env)
{
	int		shlvl;
	char	*new_shlvl;

	if (!(isatty(STDIN_FILENO)))
		exit(EXIT_FAILURE);
	var->exit_nb = 0;
	var->env = ft_strsdup(env);
	if (!var->env)
		exit(EXIT_FAILURE);
	shlvl = ft_atoi(getenv("SHLVL"));
	if (!shlvl)
		exit(EXIT_FAILURE);
	new_shlvl = ft_itoa(shlvl + 1);
	if (ft_update_env_var_value_from_key(&var->env, "SHLVL", new_shlvl) == FAILURE)
	{
		free(new_shlvl);
		exit(EXIT_FAILURE);
	}
	free(new_shlvl);
	if (!var->env)
		exit(EXIT_FAILURE);
	ft_disable_echoctl();
	ft_set_sigquit_reception_handler();
	ft_set_sigint_reception_handler();
}
