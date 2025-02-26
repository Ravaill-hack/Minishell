/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:26:43 by julien            #+#    #+#             */
/*   Updated: 2025/02/26 11:01:26 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_cmd(t_var *var, t_shell shell, char *val)
{
	if (ft_strncmp(val, "exit", ft_strlen(val)) == 0)
		return (ft_cmd_exit(*var, shell, var->env, *(var->token_list)));
	else if (ft_strncmp(val, "env", ft_strlen(val)) == 0)
		ft_cmd_env(var->env, *(var->token_list));
	else if (ft_strncmp(val, "unset", 5) == 0)
		return (ft_cmd_unset(&var->env, *(var->token_list)));
	else if (ft_strncmp(val, "export", 6) == 0)
		return (ft_cmd_export(&var->env, *(var->token_list)));
	else if (ft_strncmp(val, "pwd", ft_strlen(val)) == 0)
		return (ft_cmd_pwd(var->env, *(var->token_list)));
	else if (ft_strncmp(val, "cd", 2) == 0)
		return (ft_cmd_cd(&var->env, *(var->token_list)));
	else if (ft_strncmp(val, "echo", 4) == 0)
		return (ft_cmd_echo(*(var->token_list), var->env, var->exit_nb));
	else
		return (ft_exec_cmd(var->env, val));
	return (SUCCESS);
}
