/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:26:27 by julien            #+#    #+#             */
/*   Updated: 2025/03/02 10:36:16 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_exit(t_var var, t_shell shell, char ***env, t_cmd *node)
{
	int		shlvl;
	int		shlvl_current;
	int		status;

	if (!(node->arg[1]))
	{
		shlvl = ft_atoi(getenv("SHLVL")) + 1;
		if (!shlvl)
			return (FAILURE);
		shlvl_current = ft_atoi((ft_extract_env_value_from_key(*env, "SHLVL")));
		if (!shlvl_current)
			return (FAILURE);
		if (shlvl_current == shlvl)
			status = ft_handle_exit_last_shlvl(var, shell, env);
		else
			status = ft_handle_exit_not_last_shlvl(env);
		return (status);
	}
	return (FAILURE);
}

int	ft_exec_exit_cmd(char **env)
{
	char	**args;
	char	*path;
	int		status;

	args = (char **)ft_calloc(2, sizeof(char *));
	if (!args)
		return (FAILURE);
	args[0] = ft_strdup("exit");
	args[1] = NULL;
	path = ft_extract_path(env, "exit");
	if (!path)
		return (FAILURE);
	args = ft_set_exec_args(path, args);
	if (!args)
		return (ft_free_strs(args), free(path), FAILURE);
	status = execve(path, args, env);
	ft_free_strs(args);
	free(path);
	return (status);
}

int	ft_handle_exit_last_shlvl(t_var var, t_shell shell, char ***env)
{
	(void)shell;
	(void)var;
	if (!ft_update_shlvl(env, -1))
		return (FAILURE);
	if (ft_exec_exit_cmd(*env) == FAILURE)
		return (FAILURE);
	ft_clear_and_free_all(&var, &shell);
	exit(EXIT_SUCCESS);
}

int	ft_handle_exit_not_last_shlvl(char ***env)
{
	int		shlvl;
	char	*new_shlvl;
	int		status;

	ft_putstr_fd("test\n", 1);
	shlvl = ft_atoi(getenv("SHLVL"));
	if (!shlvl)
		return (FAILURE);
	new_shlvl = ft_itoa(shlvl - 1);
	status = ft_update_env_var_value_from_key(env, "SHLVL", new_shlvl);
	free(new_shlvl);
	if (status == FAILURE)
		return (status);
	printf("exit\n");
	return (ft_exec_exit_cmd(*env));
}
