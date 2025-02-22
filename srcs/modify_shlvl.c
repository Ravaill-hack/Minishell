/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:30:40 by julien            #+#    #+#             */
/*   Updated: 2025/02/22 16:31:04 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
