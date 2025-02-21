/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 10:31:57 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/21 17:34:32 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_add_env_var(char ***env_ptr, char *env_var)
{
	*env_ptr = ft_strsjoinstr(*env_ptr, env_var);
	if (!(*env_ptr))
		return (FAILURE);
	return (SUCCESS);
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

char	**ft_modify_shlvl(char **env, int lvl)
{
	int		shlvl_0;
	char	*shlvl;
	char	*shlvl_str;
	int		line_env;

	line_env = ft_get_line_env(env, "SHLVL");
	if (line_env == -1)
		return (NULL);
	shlvl_0 = ft_atoi(&env[line_env][6]);
	shlvl_str = ft_itoa(shlvl_0 + lvl);
	if (!shlvl_str)
		return (NULL);
	shlvl = ft_strjoin("SHLVL=", shlvl_str);
	if (!shlvl)
	{
		free(shlvl_str);
		return (NULL);
	}
	free(shlvl_str);
	free(env[line_env]);
	env[line_env] = shlvl;
	return (env);
}
