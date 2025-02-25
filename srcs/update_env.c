/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 10:31:57 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/25 11:35:53 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_update_env_var_value(char ***env_ptr, int line_index, char *value)
{
	char	**new_env;
	t_index	index;

	new_env = (char **)ft_calloc(ft_strslen(*env_ptr) + 1, sizeof(char *));
	if (!new_env)
		return (FAILURE);
	index.i = 0;
	index.j = 0;
	while ((*env_ptr)[index.i])
	{
		if ((index.i != line_index
				&& ft_copy_env_var(new_env, *env_ptr,
					&index.i, &index.j) == FAILURE)
			|| (index.i == line_index
				&& ft_update_env_var(new_env, *env_ptr,
					&index, value) == FAILURE))
			return (ft_free_strs(new_env), FAILURE);
		index.i++;
	}
	ft_free_strs(*env_ptr);
	*env_ptr = new_env;
	*env_ptr[index.i] = NULL;
	return (SUCCESS);
}

int	ft_copy_env_var(char **new_env, char **env, int *i, int *j)
{
	new_env[*j] = ft_strdup(env[*i]);
	if (!new_env[*j])
		return (ft_free_strs_until(new_env, *j), FAILURE);
	(*j)++;
	return (SUCCESS);
}

int	ft_update_env_var(char **new_env, char **env, t_index *index, char *value)
{
	char	*key;

	value = ft_strjoin("=", value);
	if (!value)
		return (ft_free_strs_until(new_env, index->j), FAILURE);
	key = ft_extract_key_env(env[index->i]);
	new_env[index->j] = ft_strjoin(key, value);
	free(key);
	if (!new_env[index->j])
		return (ft_free_strs_until(new_env, index->j), free(value), FAILURE);
	free(value);
	index->j++;
	return (SUCCESS);
}
