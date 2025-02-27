/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsing_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:30:22 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/27 17:35:04 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_doll_var_exists(char *str, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(str, env[i], ft_strlen(str)) == 0
			&& env[i][ft_strlen(str)] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_exit_nb_join(char *str, t_var *var)
{
	char	*nb;
	char	*joined_str;

	nb = ft_itoa(var->exit_nb);
	joined_str = ft_strjoin(nb, str);
	free(nb);
	return (joined_str);
}

char	*ft_replace_doll(char *str, t_var *var)
{
	if (!str[1])
		return (str);
	if (str[1] == '?' && !str[2])
		return (ft_itoa(var->exit_nb));
	if (str[1] == '?' && str[2])
		return (ft_exit_nb_join(&str[2], var));
	if (ft_doll_var_exists(str + 1, var->env))
		return (ft_extract_env_value_from_key(var->env, str + 1));
	else
		return (ft_strdup(""));
}

int	ft_expand_dolls(t_token_list *list, t_var *var)
{
	char	*tmp;

	tmp = NULL;
	while (list)
	{
		if (list->type == DOLL)
		{
			tmp = list->val;
			list->val = ft_replace_doll(list->val, var);
			if (tmp != list->val)
				free(tmp);
		}
		list = list->next;
	}
	return (1);
}
