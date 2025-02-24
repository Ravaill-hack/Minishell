/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:26:27 by julien            #+#    #+#             */
/*   Updated: 2025/02/24 13:17:23 by juduchar         ###   ########.fr       */
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
	int	shlvl;

	shlvl = ft_atoi(getenv("SHLVL"));
	if (ft_update_env_var_value(&env, ft_get_line_env(env, "SHLVL"),
			ft_itoa(shlvl - 1)) == FAILURE)
		return (FAILURE);
	if (ft_exec_cmd(env, "exit") == FAILURE)
		return (FAILURE);
	ft_clear_and_free_all(var);
	exit(EXIT_SUCCESS);
}

int	ft_handle_exit_not_last_shlvl(char **env)
{
	int	shlvl;

	shlvl = ft_atoi(getenv("SHLVL"));
	if (ft_update_env_var_value(&env, ft_get_line_env(env, "SHLVL"),
			ft_itoa(shlvl - 1)) == FAILURE)
		return (FAILURE);
	printf("exit\n");
	return (ft_exec_cmd(env, "exit"));
}

void	ft_cmd_env(char **env, t_token_list *token_list)
{
	if (!token_list->next)
		ft_print_strs(env);
}

int	ft_cmd_unset(char ***env_ptr, t_token_list *token_list)
{
	int		line_index;
	char	**split_line;

	split_line = ft_split(token_list->val, ' ');
	if (!split_line[1])
		return (FAILURE);
	line_index = ft_get_line_env(*env_ptr, split_line[1]);
	if (line_index == -1)
		return (FAILURE);
	else
		return (ft_remove_env_var(env_ptr, line_index));
	return (SUCCESS);
}
