/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:28:54 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/23 22:02:22 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_echo_print_doll(t_token_list *token, char **env, int exit_nb)
{
	char	*temp;

	if (token->val[1] == '?')
	{
		ft_putnbr_fd(exit_nb, 1);
		return (SUCCESS);
	}
	temp = ft_extract_env_value_from_key(env, &(token->val[1]));
	if (temp)
	{
		ft_putstr_fd (temp, 1);
		//free (temp);
		return (SUCCESS);
	}
	return (FAILURE);
}

int	ft_cmd_echo_print_tokens(t_token_list *token, int i, char **env, int ex_nb)
{
	if (token->type != CONTENT && token->type != DOLL)
		return (FAILURE);
	while (ft_isspace(token->val[i]))
		i++;
	while (token && (token->type == CONTENT || token->type == DOLL))
	{
		if (token->type == DOLL)
			ft_cmd_echo_print_doll(token, env, ex_nb);
		else if (token->type == CONTENT && token->dq_end == 0
			&& token->dq_start == 0)
			ft_cmd_echo_print_str(token->val, i, 1);
		else if (token->type == CONTENT && (token->dq_end != 0
			|| token->dq_start != 0))
			ft_cmd_echo_print_str(token->val, i, 0);
		if (token->print_space_after == 1)
			ft_putchar_fd(' ', 1);
		i = 0;
		token = token->next;
	}
	return (SUCCESS);
}

int	ft_cmd_echo(t_token_list *token, char **env, int ex_nb)
{
	size_t	i;
	int		ind;
	int		success;

	success = 0;
	ind = ft_cmd_skip_name(token->val);
	if (token->val[ind] == '\0')
		token = token->next;
	if (token->type == CONTENT || token->type == DOLL)
	{
		while (ft_isspace(token->val[ind]))
			ind++;
		if ((token->val[ind] == '-' && token->val[ind + 1] == 'n')
			&& (token->val[ind + 2] == ' ' || token->val[ind + 2] == '\0'))
		{
			i = 2;
			ind += 2;
		}
		else
			i = 1;
		success = ft_cmd_echo_print_tokens(token, ind, env, ex_nb);
		if (i == 1)
			ft_putchar_fd('\n', 1);
	}
	return (success);
}
