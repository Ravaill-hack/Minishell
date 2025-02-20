/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 10:31:57 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/20 11:56:47 by juduchar         ###   ########.fr       */
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

char	**ft_modify_shlvl(char **env, int lvl)
{
	int 	shlvl_0;
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

