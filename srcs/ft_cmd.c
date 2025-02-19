/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:26:27 by julien            #+#    #+#             */
/*   Updated: 2025/02/19 16:50:58 by juduchar         ###   ########.fr       */
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
/*
int	ft_add_env_var(t_var *var, int line)
{
	char	**new_env;
	int		i;
	int		len;

	len = ft_strslen(var->env);
	new_env = ft_calloc(sizeof(char *), (len + 2));
	if (!new_env)
		return (FAILURE);
	new_env[len + 1] = ;
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
*/

void	ft_cmd_export(t_var *var)
{
	size_t	i;
	size_t	len;

	//char	**key_value;
	char	*key;
	char	*value;

	if (!var->token_list[0]->next)
	{
		i = 0;
		len = ft_strslen(var->env);
		while (i < len)
		{
			printf("declare -x ");
			printf("%s", var->env[i]);
			printf("\n");
			i++;
		}
	}
	if (var->token_list[0]->next)
	{
		char	*eq_ptr;
		
		eq_ptr = ft_strchr(var->token_list[0]->next->val, '=');
		key = ft_substr(var->token_list[0]->next->val, 0, eq_ptr - var->token_list[0]->next->val);
		printf("key = %s\n", key);
		value = ft_substr(eq_ptr + 1, 0, ft_strlen(var->token_list[0]->next->val));
		printf("value = %s\n", value);
		// /!\ if the value contains an env var ($PATH for example)
		// replace this by the value of the env var
		//if (ft_get_line_env(var.env, var.token_list[0]) == -1)
						
	}
					// split with = (key=value)
					
					// add this value to env
					// if key is an env var
					// that is present in env
					// update this value in env
					// /!\ with a value of $var
					// replace $var with the value of var in env
					// example : export PATH=$PATH:/chemin/test
					// check if the value after $ in uppercase is an env var
					// take the value of this env var
					// concatenate with the string after this env var
					// and replace the env var with this new string
}