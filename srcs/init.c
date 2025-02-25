/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:26:01 by julien            #+#    #+#             */
/*   Updated: 2025/02/25 09:06:32 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_update_shlvl(char ***env, int level)
{
	int		shlvl;
	char	*new_shlvl;

	shlvl = ft_atoi(getenv("SHLVL"));
	if (!shlvl)
		return (FAILURE);
	new_shlvl = ft_itoa(shlvl + level);
	if (ft_update_env_var_value_from_key(env, "SHLVL", new_shlvl) == FAILURE)
	{
		free(new_shlvl);
		return (FAILURE);
	}
	free(new_shlvl);
	return (SUCCESS);
}

void	ft_init(t_var *var, char **env)
{
	if (!(isatty(STDIN_FILENO)))
		exit(EXIT_FAILURE);
	var->exit_nb = 0;
	var->env = ft_strsdup(env);
	if (!var->env)
		exit(EXIT_FAILURE);
	if (!ft_update_shlvl(&var->env, 1))
		exit(EXIT_FAILURE);
	ft_disable_echoctl();
	ft_set_sigquit_reception_handler();
	ft_set_sigint_reception_handler();
}
