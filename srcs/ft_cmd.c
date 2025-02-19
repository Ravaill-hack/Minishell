/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:26:27 by julien            #+#    #+#             */
/*   Updated: 2025/02/19 11:38:47 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*temp;
	char	*res;

	temp = ft_strjoin(s1, s2);
	res = ft_strjoin(temp, s3);
	free(temp);
	return (res);
}

char	*extract_env(char *title, char **env)
{
	int	i;
	int	j;

	i = ft_get_line_env(env, title);
	j = 0;
	if (i == -1 || !env[i])
		return (NULL);
	while (env[i][j] && env[i][j] != '=')
		j++;
	return (env[i] + j + 1);
}

char	*extract_path(char *cmd, char **env)
{
	int		i;
	char	**raw;
	char	**name_cmd;
	char	*path;

	i = 0;
	raw = ft_split(extract_env("PATH", env), ':');
	name_cmd = ft_split(cmd, ' ');
	while (raw[i])
	{
		path = ft_strjoin3(raw[i], "/", name_cmd[0]);
		if (access(path, F_OK | X_OK) == 0)
		{
			ft_free_strs(raw);
			ft_free_strs(name_cmd);
			return (path);
		}
		if (path)
			free(path);
		i++;
	}
	if (raw)
		ft_free_strs(raw);
	ft_free_strs(name_cmd);
	return (cmd);
}

int	exec_cmd(char *cmd, char **env)
{
	char	**split_cmd;
	char	*path;
	int		err;

	split_cmd = ft_split(cmd, ' ');
	path = extract_path(split_cmd[0], env);
	err = execve(path, split_cmd, env);
	if (err == -1)
	{
		ft_free_strs(split_cmd);
		free(path);
		return(FAILURE);
	}
	return (SUCCESS);
}

int ft_cmd_exit(t_var var)
{
	if (!var.token_list[0]->next)
	{
		int	shlvl;
		int	shlvl_current;

		shlvl = ft_atoi(getenv("SHLVL"));
		if (!shlvl)
			return (FAILURE);
        shlvl_current = ft_get_line_env(var.env, "SHLVL");
		if (shlvl_current == shlvl + 1)
		{
			//ft_clear_and_free_all(var);
			// TO FIX
			if (exec_cmd("exit", var.env) == FAILURE)
				return (FAILURE);
			return (SUCCESS);
		}
		if (!ft_modify_shlvl(var.env, shlvl -1))
            return (FAILURE);
		/*
		ft_clear_and_free_all(var);
		if (exec_cmd("exit", var.env) == FAILURE)
			return (FAILURE);
		*/
		return (SUCCESS);
	}
	return (FAILURE);
}

void	ft_cmd_env(t_var var)
{
	if (!var.token_list[0]->next)
		ft_print_strs(var.env);
}

int	ft_remove_env_var(t_var *var, int line)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = ft_calloc(sizeof(char *), (ft_strslen(var->env)));
	if (!new_env)
		return (FAILURE);
	i = 0;
	j = 0;
	while (var->env[i])
	{
		if (i != line)
		{
			new_env[j] = ft_strdup(var->env[i]);
			if (!new_env[j])
			{
				ft_free_strs_until(new_env, j);
				return (FAILURE);
			}
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	ft_free_strs(var->env);
	var->env = new_env;
	return (SUCCESS);
}

int	ft_cmd_unset(t_var *var)
{
	char	*env_var;
	int		line;

	if (!var->token_list[0]->next)
		return (FAILURE);
	env_var = ft_strdup(var->token_list[0][1].val);
	line = ft_get_line_env(var->env, env_var);
	if (line == -1)
		return (FAILURE);
	ft_remove_env_var(var, line);
	return (SUCCESS);
}