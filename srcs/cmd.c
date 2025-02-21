/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:26:27 by julien            #+#    #+#             */
/*   Updated: 2025/02/21 11:15:54 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cmd_exit(t_var var, char **env, t_token_list *token_list)
{
	int	shlvl;
	int	shlvl_current;

	if (!token_list->next)
	{
		shlvl = ft_atoi(getenv("SHLVL"));
		if (!shlvl)
			return (FAILURE);
        shlvl_current = ft_atoi((extract_env_value_from_key(env, "SHLVL")));
		if (exec_cmd(env, "exit") == SUCCESS)
		{
			if (!ft_modify_shlvl(env, -1))
            	return (FAILURE);
			if (shlvl_current == shlvl)
			{
				ft_clear_and_free_all(var);
				exit(EXIT_SUCCESS);
			}
			else
				return (SUCCESS);
		}
	}
	return (FAILURE);
}

void	ft_cmd_env(char **env, t_token_list *token_list)
{
	if (!token_list->next)
		ft_print_strs(env);
}


int	ft_cmd_unset(char ***env_ptr, t_token_list *token_list)
{
	int		line_index;
	char	**split_line;

	split_line = ft_split(token_list->val, ' ');
	if (!split_line[1])
		return (FAILURE);
	line_index = ft_get_line_env(*env_ptr, split_line[1]);
	if (line_index == -1)
		return (FAILURE);
	else
	{
		if (ft_remove_env_var(env_ptr, line_index) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
int	ft_cmd_export(char ***env_ptr, t_token_list *token_list)
{
	char	**split_line;
	size_t	i;
	size_t	len;
	char	*key;
	char	*value;
	int		line_index;

	split_line = ft_split(token_list->val, ' ');
	if (!split_line[1])
	{
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
	else
	{
		key = ft_strdup(ft_extract_key_env(split_line[1]));
		value = ft_strdup(ft_extract_value_env(split_line[1]));
		if (!key || !*key || !value || !*value)
			return (FAILURE);
		line_index = ft_get_line_env(*env_ptr, key);
		if (line_index == -1)
		{
			if (ft_add_env_var(env_ptr, split_line[1]) == FAILURE)
				return (FAILURE);
			return (SUCCESS);
		}
		else
		{
			if (ft_update_env_var_value(env_ptr, line_index, value) == FAILURE)
				return (FAILURE);
			return (SUCCESS);
		}
	}
	return (FAILURE);
}

int	ft_cmd_pwd(char **env, t_token_list *token_list)
{
	char	**split_line;

	split_line = ft_split(token_list->val, ' ');
	if (!split_line[1])
	{
		printf("%s\n", extract_env_value_from_key(env, "PWD"));
		return (SUCCESS);
	}
	return (FAILURE);
}
