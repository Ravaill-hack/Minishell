/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:15:56 by juduchar          #+#    #+#             */
/*   Updated: 2025/02/25 10:21:22 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_export(char ***env_ptr, t_token_list *token_list)
{
	char	**split_line;
	int		result;

	split_line = ft_split(token_list->val, ' ');
	if (!split_line[1])
		result = ft_cmd_export_with_no_args(env_ptr);
	else
		result = ft_cmd_export_with_args(env_ptr, split_line[1]);
	ft_free_strs(split_line);
	return (result);
}

int	ft_cmd_export_with_no_args(char ***env_ptr)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strslen(*env_ptr);
	while (i < len)
	{
		printf("declare -x ");
		printf("%s", (*env_ptr)[i]);
		printf("\n");
		i++;
	}
	return (SUCCESS);
}

int	ft_cmd_export_with_args(char ***env_ptr, char *arg)
{
	char	*key;
	char	*value;
	int		line_index;
	int		result;

	key = ft_extract_key_env(arg);
	value = ft_extract_value_env(arg);
	if (!key || !*key || !value || !*value)
		return (FAILURE);
	line_index = ft_get_line_env(*env_ptr, key);
	free(key);
	if (line_index == -1)
		result = ft_add_env_var(env_ptr, arg);
	else
		result = ft_update_env_var_value(env_ptr, line_index, value);
	free(value);
	return (result);
}

int	ft_cmd_pwd(char **env, t_token_list *token_list)
{
	char	**split_line;

	split_line = ft_split(token_list->val, ' ');
	if (!split_line[1])
	{
		printf("%s\n", ft_extract_env_value_from_key(env, "PWD"));
		return (ft_free_strs(split_line), SUCCESS);
	}
	return (ft_free_strs(split_line), FAILURE);
}
