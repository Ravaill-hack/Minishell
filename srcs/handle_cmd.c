/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:26:43 by julien            #+#    #+#             */
/*   Updated: 2025/02/26 19:19:50 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_cmd(t_var *var, char *val)
{
	if (ft_strncmp(val, "exit", ft_strlen(val)) == 0)
		return (ft_cmd_exit(*var, var->env, *(var->token_list)));
	else if (ft_strncmp(val, "env", ft_strlen(val)) == 0)
		ft_cmd_env(var->env, *(var->token_list));
	return (FAILURE);
}

t_token_list *ft_first_operand(t_token_list *list)
{
	t_token_list	*temp;

	temp = list;
	while (temp && (temp->type == STR || temp->type == PIPE))
		temp = temp->next;
	if (temp != list)
		return (temp);
	return (NULL);
}

t_token_list *ft_last_operand(t_token_list *list)
{
	t_token_list	*temp;

	temp = ft_last_token(list);
	while (temp && (temp->type == STR || temp->type == PIPE))
		temp = temp->prev;
	if (temp != ft_last_token(list))
		return (temp);
	return (NULL);
}
/*
int	ft_handle_one_cmd(t_var *var, char *val, int opt_in, int opt_out)
{

}

int	ft_choose_how_to_handle(t_var *var, char *val)
{
	
}
*/

