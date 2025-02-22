/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 10:31:57 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/22 16:31:07 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_update_env_var_value(char ***env_ptr, int line_index, char *value)
{
	char	**new_env;
	int		i;
	int		j;
	int		indices[2];

	new_env = (char **)ft_calloc(ft_strslen(*env_ptr), sizeof(char *));
	if (!new_env)
		return (FAILURE);
	i = 0;
	j = 0;
	while ((*env_ptr)[i])
	{
		indices[0] = i;
		indices[1] = j;
		if (i != line_index)
			return (ft_copy_env_var(new_env, *env_ptr, &i, &j));
		else
			return (ft_update_env_var(new_env, *env_ptr, indices, value));
		i++;
	}
	new_env[j] = NULL;
	ft_free_strs(*env_ptr);
	*env_ptr = new_env;
	return (SUCCESS);
}

int	ft_copy_env_var(char **new_env, char **env_ptr, int *i, int *j)
{
	new_env[*j] = ft_strdup(env_ptr[*i]);
	if (!new_env[*j])
		return (ft_free_strs_until(new_env, *j), FAILURE);
	(*j)++;
	return (SUCCESS);
}

int	ft_update_env_var(char **new_env, char **env_ptr, int *indices, char *value)
{
	int	i;
	int	j;

	i = indices[0];
	j = indices[1];
	value = ft_strjoin("=", value);
	if (!value)
		return (ft_free_strs_until(new_env, j), FAILURE);
	new_env[j] = ft_strjoin(ft_extract_key_env(env_ptr[i]), value);
	if (!new_env[j])
		return (ft_free_strs_until(new_env, j), free(value), FAILURE);
	free(value);
	indices[1]++;
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
