/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 10:31:57 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/18 15:06:19 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_line_env(char **env, char *title)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], title, ft_strlen(title)) != 0)
		i++;
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

	line_env = ft_get_line_env(env, "SHLVL=");
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

