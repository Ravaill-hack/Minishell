/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:58:43 by juduchar          #+#    #+#             */
/*   Updated: 2025/02/25 11:24:58 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_update_env_var_value_from_key(char ***env, char *key, char *value)
{
	int		index;

	if (!env || !*env || !key || !value)
		return (FAILURE);
	index = ft_get_line_env(*env, key);
	if (index == -1)
		return (FAILURE);
	if (ft_update_env_var_value(env, index, value) == FAILURE)
		return (FAILURE);
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
