/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:28:54 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/24 14:12:07 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (SUCCESS);
	}
	return (SUCCESS);
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

int	ft_cmd_skip_name(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] && str[i] == '\"')
	{
		while (str[i] && str[i] != '\"')
			i++;
		i++;
	}
	else if (str[i] && str[i] == '\'')
	{
		while (str[i] && str[i] != '\'')
			i++;
		i++;
	}
	else if (str[i])
	{
		while (str[i] && !ft_isspace(str[i]))
			i++;
	}
	return (i);
}

int	ft_cmd_echo_print_str(char *str, int i, int opt)
{
	// si l'option est a 1 ca veut dire qu'on ne veut pas recopier
	// tous les espaces, sinon on copie tel quel
	if (opt == 1)
	{
		while (str[i])
		{
			while (str[i] && ft_isspace(str[i]))
				i++;
			while (str[i] && !ft_isspace(str[i]))
			{
				ft_putchar_fd(str[i], 1);
				i++;
			}
			if (str[i] != '\0' && ft_isspace(str[i]))
				ft_putchar_fd(' ', 1);
		}
	}
	else
	{
		while (str[i])
		{
			ft_putchar_fd(str[i], 1);
			i++;
		}
	}
	return (SUCCESS);
}
