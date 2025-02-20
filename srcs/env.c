/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 10:31:57 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/20 09:52:42 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_line_env(char **env, char *title)
{
	int		i;
	char	*key;

	i = 0;

	while (env[i])
	{
		key = ft_extract_key_env(env[i]);
		if (ft_strncmp(key, title, ft_strlen(title)) == 0)
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

char	**ft_modify_shlvl(char **env, int ind)
{
	int 	shlvl_0;;
	char	*shlvl;
	char	*shlvl_str;
	int		line_env;

	line_env = ft_get_line_env(env, "SHLVL");
	shlvl_0 = ft_atoi(&env[line_env][6]);
	shlvl_str = ft_itoa(shlvl_0 + ind);
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

