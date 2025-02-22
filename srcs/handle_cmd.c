/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:26:43 by julien            #+#    #+#             */
/*   Updated: 2025/02/22 16:01:37 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_cmd(t_var *var, char *val)
{
	if (ft_strncmp(val, "exit", ft_strlen(val)) == 0)
		return (ft_cmd_exit(*var, var->env, *(var->token_list)));
	else if (ft_strncmp(val, "env", ft_strlen(val)) == 0)
		ft_cmd_env(var->env, *(var->token_list));
	else if (ft_strncmp(val, "unset", 5) == 0)
		return (ft_cmd_unset(&var->env, *(var->token_list)));
	else if (ft_strncmp(val, "export", 6) == 0)
		return (ft_cmd_export(&var->env, *(var->token_list)));
	else if (ft_strncmp(val, "pwd", ft_strlen(val)) == 0)
		return (ft_cmd_pwd(var->env, *(var->token_list)));
	else if (ft_strncmp(val, "cd", 2) == 0)
		return (ft_cmd_cd(var->env, *(var->token_list)));
	else if (ft_strncmp(val, "echo", 4) == 0)
		return (ft_cmd_echo(*(var->token_list)));
	return (FAILURE);
}
