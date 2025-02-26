/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:26:27 by julien            #+#    #+#             */
/*   Updated: 2025/02/26 19:17:28 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_exit(t_var var, char **env, t_token_list *token_list)
{
	int	shlvl;
	int	shlvl_current;

	if (!token_list->next)
	{
		shlvl = ft_atoi(getenv("SHLVL"));
		if (!shlvl)
			return (FAILURE);
		shlvl_current = ft_atoi((ft_extract_env_value_from_key(env, "SHLVL")));
		if (shlvl_current == shlvl)
			return (ft_handle_exit_last_shlvl(var, env));
		else
			return (ft_handle_exit_not_last_shlvl(env));
	}
	return (FAILURE);
}

int	ft_handle_exit_last_shlvl(t_var var, char **env)
{
	if (ft_modify_shlvl(env, -1))
		return (FAILURE);
	if (ft_exec_cmd(env, "exit") == FAILURE)
		return (FAILURE);
	ft_clear_and_free_all(var);
	exit(EXIT_SUCCESS);
}

int	ft_handle_exit_not_last_shlvl(char **env)
{
	if (ft_modify_shlvl(env, -1))
		return (FAILURE);
	printf("exit\n");
	if (ft_exec_cmd(env, "exit") == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

void	ft_cmd_env(char **env, t_token_list *token_list)
{
	if (!token_list->next)
		ft_print_strs(env);
}

