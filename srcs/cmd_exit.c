/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:26:27 by julien            #+#    #+#             */
/*   Updated: 2025/02/27 16:07:32 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_exit(t_var var, t_shell shell, char ***env, t_token_list *token_list)
{
	int		shlvl;
	int		shlvl_current;
	char	**split_cmd;
	int		status;

	if (!token_list->next)
	{
		split_cmd = ft_split(token_list->val, ' ');
		if (!split_cmd || !split_cmd[0])
			return (ft_free_strs(split_cmd), FAILURE);
		shlvl = ft_atoi(getenv("SHLVL")) + 1;
		if (!shlvl)
			return (FAILURE);
		shlvl_current = ft_atoi((ft_extract_env_value_from_key(*env, "SHLVL")));
		if (!shlvl_current)
			return (FAILURE);
		if (shlvl_current == shlvl)
			status = ft_handle_exit_last_shlvl(var, shell, env, split_cmd);
		else
			status = ft_handle_exit_not_last_shlvl(env, split_cmd);
		return (ft_free_strs(split_cmd), status);
	}
	return (FAILURE);
}

int	ft_exec_exit_cmd(char **env, char **split_cmd)
{
	char	**args;
	char	*path;

	path = ft_extract_path(env, split_cmd[0]);
	if (!path)
		return (ft_free_strs(split_cmd), FAILURE);
	args = ft_set_exec_args(path, split_cmd);
	if (!args)
		return (ft_free_strs(split_cmd), free(path), FAILURE);
	if (!execve(path, args, env))
		return (FAILURE);
	return (SUCCESS);
}

int	ft_handle_exit_last_shlvl(t_var var, t_shell shell,
	char ***env, char **split_cmd)
{
	if (!ft_update_shlvl(env, -1))
		return (FAILURE);
	if (ft_exec_exit_cmd(*env, split_cmd) == FAILURE)
		return (FAILURE);
	ft_clear_and_free_all(var, shell);
	exit(EXIT_SUCCESS);
}

int	ft_handle_exit_not_last_shlvl(char ***env, char **split_cmd)
{
	int		shlvl;
	char	*new_shlvl;

	shlvl = ft_atoi(getenv("SHLVL"));
	if (!shlvl)
		return (FAILURE);
	new_shlvl = ft_itoa(shlvl - 1);
	if (ft_update_env_var_value_from_key(env, "SHLVL", new_shlvl) == FAILURE)
	{
		free(new_shlvl);
		return (FAILURE);
	}
	//printf("exit\n");
	if (ft_exec_exit_cmd(*env, split_cmd) == FAILURE)
		return (FAILURE);
	_exit(0);
}
