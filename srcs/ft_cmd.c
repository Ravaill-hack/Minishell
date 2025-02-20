/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:26:27 by julien            #+#    #+#             */
/*   Updated: 2025/02/20 22:30:10 by julien           ###   ########.fr       */
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

char	*extract_env_value_from_key(char **env, char *env_var_key)
{
	int	i;
	int	j;

	i = ft_get_line_env(env, env_var_key);
	j = 0;
	if (i == -1 || !env[i])
		return (NULL);
	while (env[i][j] && env[i][j] != '=')
		j++;
	return (env[i] + j + 1);
}

char	*extract_path(char **env, char *cmd)
{
	int		i;
	char	**raw;
	char	**name_cmd;
	char	*path;

	i = 0;
	raw = ft_split(extract_env_value_from_key(env, "PATH"), ':');
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

int	exec_cmd(char **env, char *cmd)
{
	char	**split_cmd;
	char	*path;
	char	**args;
	int		err;

	split_cmd = ft_split(cmd, ' ');
	path = extract_path(env, split_cmd[0]);
	args = ft_set_exec_args(path, split_cmd);
	if (!args)
		return (ft_free_strs(split_cmd), free(path), FAILURE);
	err = execve(path, args, env);
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

int ft_cmd_exit(t_var var, char **env, t_token_list *token_list)
{
	int	shlvl;
	int	shlvl_current;

	if (!token_list->next)
	{
		shlvl = ft_atoi(getenv("SHLVL"));
		if (!shlvl)
			return (FAILURE);
        shlvl_current = ft_atoi((extract_env_value_from_key(env, "SHLVL")));
		if (exec_cmd(env, "exit") == SUCCESS)
		{
			if (!ft_modify_shlvl(env, -1))
            	return (FAILURE);
			if (shlvl_current == shlvl)
			{
				ft_clear_and_free_all(var);
				exit(EXIT_SUCCESS);
			}
			else
				return (SUCCESS);
		}
	}
	return (FAILURE);
}

void	ft_cmd_env(char **env, t_token_list *token_list)
{
	if (!token_list->next)
		ft_print_strs(env);
}

int	ft_remove_env_var(char ***env_ptr, int line_index)
{
	char	**new_env;
	int		i;
	int		j;
	
	new_env = (char **)ft_calloc(ft_strslen(*env_ptr), sizeof(char *));
	if (!new_env)
		return (FAILURE);
	i = 0;
	j = 0;
	while ((*env_ptr)[i])
	{
		if (i != line_index)
		{
			new_env[j] = ft_strdup((*env_ptr)[i]);
			if (!new_env[j])
				return (ft_free_strs_until(new_env, j), FAILURE);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	ft_free_strs(*env_ptr);
	*env_ptr = new_env;
	return (SUCCESS);
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
	{
		if (ft_remove_env_var(env_ptr, line_index) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	ft_add_env_var(char ***env_ptr, char *env_var)
{
	*env_ptr = ft_strsjoinstr(*env_ptr, env_var);
	if (!(*env_ptr))
		return (FAILURE);
	return (SUCCESS);
}


int	ft_update_env_var_value(char ***env_ptr, int line_index, char *value)
{
	char	**new_env;
	int		i;
	int		j;
	
	new_env = (char **)ft_calloc(ft_strslen(*env_ptr), sizeof(char *));
	if (!new_env)
		return (FAILURE);
	i = 0;
	j = 0;
	while ((*env_ptr)[i])
	{
		if (i != line_index)
		{
			new_env[j] = ft_strdup((*env_ptr)[i]);
			if (!new_env[j])
				return (ft_free_strs_until(new_env, j), FAILURE);
			j++;
		}
		else
		{
			value = ft_strjoin("=", value);
			if (!value)
				return (ft_free_strs_until(new_env, j), FAILURE);
			new_env[j] = ft_strjoin(ft_extract_key_env((*env_ptr)[i]), value);
			if (!new_env[j])
				return (ft_free_strs_until(new_env, j), free(value), FAILURE);
			free(value);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	ft_free_strs(*env_ptr);
	*env_ptr = new_env;
	return (SUCCESS);
}

char	*ft_extract_key_env(char *env_var)
{
	char	*eq_ptr;
	char	*key;

	if (!env_var)
		return (NULL);
	eq_ptr = ft_strchr(env_var, '=');
	if (!eq_ptr)
		return (NULL);
	key = ft_substr(env_var, 0, eq_ptr - env_var);
	if (!key)
		return (NULL);
	return (key);
}

char	*ft_extract_value_env(char *env_var)
{
	char	*eq_ptr;
	char	*value;

	if (!env_var)
		return (NULL);
	eq_ptr = ft_strchr(env_var, '=');
	if (!eq_ptr)
		return (NULL);
	value = ft_substr(eq_ptr + 1, 0, ft_strlen(env_var));
	if (!value)
		return (NULL);
	return (value);
}

int	ft_cmd_export(char ***env_ptr, t_token_list *token_list)
{
	char	**split_line;
	size_t	i;
	size_t	len;
	char	*key;
	char	*value;
	int		line_index;

	split_line = ft_split(token_list->val, ' ');
	if (!split_line[1])
	{
		i = 0;
		len = ft_strslen(*env_ptr);
		while (i < len)
		{
			printf("declare -x ");
			printf("%s", (*env_ptr)[i]);
			printf("\n");
			i++;
		}
		return (SUCCESS);
	}
	else
	{
		key = ft_strdup(ft_extract_key_env(split_line[1]));
		value = ft_strdup(ft_extract_value_env(split_line[1]));
		printf("key = %s\n", key);
		printf("value = %s\n", value);
		if (!key || !*key || !value || !*value)
			return (FAILURE);
		line_index = ft_get_line_env(*env_ptr, key);
		if (line_index == -1)
		{
			if (ft_add_env_var(env_ptr, split_line[1]) == FAILURE)
				return (FAILURE);
			return (SUCCESS);
		}
		else
		{
			if (ft_update_env_var_value(env_ptr, line_index, value) == FAILURE)
				return (FAILURE);
			return (SUCCESS);
		}
	}
	return (FAILURE);
}

int	ft_cmd_pwd(char **env, t_token_list *token_list)
{
	char	**split_line;

	split_line = ft_split(token_list->val, ' ');
	if (!split_line[1])
	{
		printf("%s\n", extract_env_value_from_key(env, "PWD"));
		return (SUCCESS);
	}
	return (FAILURE);
}

int	ft_cmd_cd(char **env, t_token_list *token_list)
{
	char	**split_line;
	char	*path;
	char	*old_pwd;
	char	*new_pwd;

	split_line = ft_split(token_list->val, ' ');
	if (!split_line[1])
	{
		path = extract_env_value_from_key(env, "HOME");
		if (!path)
			return (FAILURE);
		exec_cmd(env, ft_strjoin("cd ", path));
		new_pwd = path;
		if (ft_update_env_var_value(&env, ft_get_line_env(env, "PWD"), new_pwd) == FAILURE)
			return (FAILURE);
		return (SUCCESS);
	}
	else
	{
		path = split_line[1];
		old_pwd = extract_env_value_from_key(env, "PWD");
		if (!old_pwd)
			return (FAILURE);
		path = ft_strjoin(old_pwd, path);
		if (exec_cmd(env, ft_strjoin("cd ", path)) == FAILURE)
			return (FAILURE);
		new_pwd = path;
		if (ft_update_env_var_value(&env, ft_get_line_env(env, "PWD"), new_pwd) == FAILURE)
			return (FAILURE);
		return (SUCCESS);
	}
}

int	ft_cmd_echo(t_token_list *token_list)
{
	char	**split_line;
	size_t	i;

	split_line = ft_split(token_list->val, ' ');
	if (split_line[1])
	{
		if (ft_strncmp(split_line[1], "-n", 2) == 0)
			i = 2;
		else
			i = 1;
		while (split_line[i])
		{
			printf("%s", split_line[i]);
			if (split_line[i + 1])
				printf(" ");
			i++;
		}
		if (ft_strncmp(split_line[1], "-n", 2) != 0)
			printf("\n");
	}
	return (SUCCESS);
}