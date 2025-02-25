/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:11:49 by juduchar          #+#    #+#             */
/*   Updated: 2025/02/25 10:10:55 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_line_env(char **env, char *env_var_key)
{
	int		i;
	char	*key;

	i = 0;
	while (env[i])
	{
		key = ft_extract_key_env(env[i]);
		if (ft_strncmp(key, env_var_key, ft_strlen(env_var_key)) == 0)
		{
			free(key);
			return (i);
		}
		free(key);
		i++;
	}
	if (!env[i])
		return (-1);
	return (i);
}

char	*ft_extract_env_value_from_key(char **env, char *env_var_key)
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
