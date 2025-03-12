/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 09:09:27 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/03/12 09:40:19 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_len_doll_hd(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$' && str[i] != '\"' && str[i] != '\''
		&& ft_isspace(str[i]) == 0)
		i++;
	return (i);
}

int	ft_doll_var_exists_hd(char *str, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(str, env[i], ft_len_doll_hd(str)) == 0
			&& env[i][ft_len_doll_hd(str)] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_extract_env_value_hd(char **env, char *env_var_key)
{
	int	i;
	int	j;

	i = ft_get_line_env_hd(env, env_var_key);
	j = 0;
	if (i == -1 || !env[i])
		return (NULL);
	while (env[i][j] && env[i][j] != '=')
		j++;
	return (env[i] + j + 1);
}

int	ft_get_line_env_hd(char **env, char *env_var_key)
{
	int		i;
	char	*key;

	i = 0;
	while (env[i])
	{
		key = ft_extract_key_env(env[i]);
		if (ft_strncmp(key, env_var_key, ft_len_doll_hd(env_var_key)) == 0)
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

int	ft_heredoc_find_len(char *str, int i, int len)
{
	while (str[i + len] && !ft_isspace(str[i + len + 1])
		&& str[i + len + 1] != '\"' && str[i + len + 1] != '\''
		&& (str[i + len + 1] != '$' || len == 0))
		len ++;
	return (len);
}
