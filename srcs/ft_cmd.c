/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:26:27 by julien            #+#    #+#             */
/*   Updated: 2025/02/20 10:58:46 by juduchar         ###   ########.fr       */
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
	return ("/bin/bash");
}

char	**ft_set_exec_args(char *path, char **split_cmd)
{
	char	**args;

	if (ft_strncmp(path, "/bin/bash", 9) == 0)
	{
		args = (char **)ft_calloc(4, sizeof(char *));
		if (!args)
			return (NULL);
		args[0] = path;
		args[1] = "-c";
		args[2] = split_cmd[0];
		args[3] = NULL;
	}
	else
		args = split_cmd;
	return (args);
}

int	exec_cmd(char *cmd, char **env)
{
	char	**split_cmd;
	char	*path;
	char	**args;
	int		err;

	split_cmd = ft_split(cmd, ' ');
	path = extract_path(split_cmd[0], env);
	args = ft_set_exec_args(path, split_cmd);
	if (!args)
		return (ft_free_strs(split_cmd), free(path), FAILURE);
	err = execve(path, split_cmd, env);
	if (err == -1)
	{
		if (args != split_cmd)
			free(args);
		ft_free_strs(split_cmd);
		free(path);
		return(FAILURE);
	}
	return (SUCCESS);
}

int ft_cmd_exit(char **env, t_token_list *token_list)
{
	int	shlvl;
	int	shlvl_current;

	if (!token_list->next)
	{
		shlvl = ft_atoi(getenv("SHLVL"));
		if (!shlvl)
			return (FAILURE);
        shlvl_current = ft_atoi(ft_extract_value_env(env[ft_get_line_env(env, "SHLVL")]));	
		if (shlvl_current == shlvl + 1)
		{
			if (!ft_modify_shlvl(env, shlvl -1))
            	return (FAILURE);
			if (exec_cmd("exit", env) == FAILURE)
				return (FAILURE);
			return (SUCCESS);
		}
		// IDEM ! TO REMOVE ?
		if (!ft_modify_shlvl(env, shlvl -1))
            return (FAILURE);
		if (exec_cmd("exit", env) == FAILURE)
			return (FAILURE);
		return (SUCCESS);
	}
	return (SUCCESS);
}

void	ft_cmd_env(char **env, t_token_list *token_list)
{
	if (!token_list->next)
		ft_print_strs(env);
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
				return (ft_free_strs_until(new_env, j), FAILURE);
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

int	ft_add_env_var(char ***env, char *line)
{
	if (!ft_strsjoinstr(*env, line))
		return (FAILURE);
	return (SUCCESS);
}

/*
int	ft_replace_env_var()
{
	
}
*/

char	*ft_extract_key_env(char *env_line)
{
	char	*eq_ptr;
	char	*key;

	eq_ptr = ft_strchr(env_line, '=');
	if (!eq_ptr)
		return (NULL);
	key = ft_substr(env_line, 0, eq_ptr - env_line);
	if (!key)
		return (NULL);
	return (key);
}

char	*ft_extract_value_env(char *env_line)
{
	char	*eq_ptr;
	char	*value;
	
	eq_ptr = ft_strchr(env_line, '=');
	if (!eq_ptr)
		return (NULL);
	value = ft_substr(eq_ptr + 1, 0, ft_strlen(env_line));
	if (!value)
		return (NULL);
	return (value);
}

int	ft_cmd_export(t_var *var)
{
	size_t	i;
	size_t	len;

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
		return (SUCCESS);
	}
	else
	{
		key = ft_extract_key_env(var->token_list[0]->next->val);
		value = ft_extract_value_env(var->token_list[0]->next->val);
		printf("key = %s\n", key);
		printf("value = %s\n", value);
		// /!\ if the value contains an env var ($PATH for example)
		// replace this by the value of the env var
		printf("ORIGINAL\n");
		ft_print_strs(var->env);
		if (ft_get_line_env(var->env, key) == -1)
		{
			if (ft_add_env_var(&var->env, var->token_list[0]->next->val) == FAILURE)
				return (FAILURE);
			printf("\n");
			printf("NEW\n");
			ft_print_strs(var->env);
			return (SUCCESS);
		}
		else
		{
			printf("var in env");
			return (SUCCESS);	
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
	return (SUCCESS);
}