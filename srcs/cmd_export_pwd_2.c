/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_pwd_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:50:23 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/11 11:02:45 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_valid_key(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]) == 1)
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (ft_strchr("-+*&@#!?:", str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_add_to_declare(char *arg, char **env, char ***declare)
{
	int	i;

	i = 0;
	if (ft_get_line_env(env, arg) != -1)
		return (0);
	while ((*declare) && (*declare)[i])
	{
		if ((ft_strncmp(arg, (*declare)[i], ft_strlen(arg)) == 0)
			&& ((*declare)[i][ft_strlen(arg)] == '\0'))
			return (0);
		i++;
	}
	*declare = ft_strsjoinstr(*declare, arg);
	return (0);
}

int	ft_cmd_export_print_declare(char **env, int i)
{
	char	*value;
	char	*key;

	ft_putstr_fd("declare -x ", 1);
	key = ft_extract_key_env(env[i]);
	ft_putstr_fd(key, 1);
	free(key);
	ft_putchar_fd('=', 1);
	ft_putchar_fd('"', 1);
	value = ft_extract_value_env((env[i]));
	ft_putstr_fd(value, 1);
	free(value);
	ft_putchar_fd('"', 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
