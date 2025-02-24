/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 10:31:57 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/24 16:49:21 by juduchar         ###   ########.fr       */
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
		if (index.i != line_index)
			ft_copy_env_var(new_env, *env_ptr, &index.i, &index.j);
		else
			ft_update_env_var(new_env, *env_ptr, &index, value);
		index.i++;
	}
	new_env[index.j] = NULL;
	ft_free_strs(*env_ptr);
	*env_ptr = new_env;
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
	value = ft_strjoin("=", value);
	if (!value)
		return (ft_free_strs_until(new_env, index->j), FAILURE);
	new_env[index->j] = ft_strjoin(ft_extract_key_env(env[index->i]), value);
	if (!new_env[index->j])
		return (ft_free_strs_until(new_env, index->j), free(value), FAILURE);
	free(value);
	index->j++;
	return (SUCCESS);
}
