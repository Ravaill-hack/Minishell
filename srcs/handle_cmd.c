/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/02/27 17:52:44 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

int	ft_handle_cmd(t_var *var, t_shell shell, char *val)
{
	if (ft_strncmp(val, "exit", ft_strlen(val)) == 0)
		return (ft_cmd_exit(*var, shell, &var->env, *(var->token_list)));
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


t_token_list *ft_first_operand(t_token_list *list)
{
	t_token_list	*temp;

	temp = list;
	while (temp && (temp->type == CONTENT || temp->type == DOLL || temp->type == PIPE))
		temp = temp->next;
	if (temp != list)
		return (temp);
	return (NULL);
}

t_token_list *ft_last_operand(t_token_list *list)
{
	t_token_list	*temp;

	temp = ft_last_token(list);
	while (temp && (temp->type == CONTENT || temp->type == DOLL || temp->type == PIPE))
		temp = temp->prev;
	if (temp != ft_last_token(list))
		return (temp);
	return (NULL);
}
