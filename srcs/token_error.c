/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:30:44 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/03/12 12:05:36 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quote_error(char *line)
{
	int	i;
	int	ns;
	int	nd;

	i = 0;
	ns = 0;
	nd = 0;
	while (line[i])
	{
		if (line[i] == '\'' && nd == 0)
			ns = !ns;
		else if (line[i] == '\"' && ns == 0)
			nd = !nd;
		i++;
	}
	if (nd != 0 || ns != 0)
	{
		ft_putstr_fd("syntax error : a quote is still open\n", 2);
		return (1);
	}
	return (0);
}

int	ft_token_redir_error(t_cmd *node, int i)
{
	char	*str;

	str = node->raw[i];
	if (((str[0] == '<' || str[0] == '>') && !(str[1]))
		|| (str[0] == '<' && str[1] == '<' && !str[2])
		|| (str[0] == '>' && str[1] == '>' && !str[2]))
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	ft_is_empty_quotes_error(char *prompt)
{
	int	i;

	i = 0;
	if (prompt[i] == 34 || prompt[i] == 39)
		i++;
	while (ft_isspace(prompt[i]) || prompt[i] == 34 || prompt[i] == 39)
	{
		if (prompt[i] == 34)
		{
			ft_putstr_fd("Command \'\' not found.\n", 2);
			return (127);
		}
		i++;
	}
	return (SUCCESS);
}

int	ft_print_err_near_tok(t_line_token tok_id)
{
	ft_putstr_fd("syntax error near unexpected token '", 2);
	if (tok_id == 0)
		ft_putstr_fd("<'\n", 2);
	else if (tok_id == 1)
		ft_putstr_fd("<<'\n", 2);
	else if (tok_id == 2)
		ft_putstr_fd(">'\n", 2);
	else if (tok_id == 3)
		ft_putstr_fd(">>'\n", 2);
	else if (tok_id == 4)
		ft_putstr_fd("|'\n", 2);
	else if (tok_id >= 5)
		ft_putstr_fd("newline'\n", 2);
	return (127);
}

int	ft_is_valid_token_list(t_token_list **token_list)
{
	t_token_list	*node;

	node = *token_list;
	if (!node)
		return (-1);
	while (node && node->next)
	{
		if (node->type <= 4 && node->next->type == 4)
			return (ft_print_err_near_tok(node->type));
		node = node->next;
	}
	if (node->type <= 4)
	{
		if (!node->prev)
			return (ft_print_err_near_tok(5));
		else
			return (ft_print_err_near_tok(node->prev->type));
	}
	return (SUCCESS);
}
