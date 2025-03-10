/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:30:44 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/03/10 10:58:21 by julien           ###   ########.fr       */
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
		return (1);
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
	if (prompt[i] == 34)
	{
		i++;
		while (ft_isspace(prompt[i]) || prompt[i] == 34)
		{
			if (prompt[i] == 34)
			{
				ft_putstr_fd("Command \'\' not found.\n", 2);
				return (127);
			}
			i++;
		}
	}
	else if (prompt[i] == 39)
	{
		i++;
		while (ft_isspace(prompt[i]) || prompt[i] == 39)
		{
			if (prompt[i] == 39)
			{
				ft_putstr_fd("Command \'\' not found.\n", 2);
				return (127);
			}
			i++;
		}
	}
	return (SUCCESS);
}

int	ft_is_error_parsing(t_var *var, char *prompt, t_shell *shell)
{
	(void)var;
	(void)shell;
	if (ft_quote_error(prompt) == 1)
		return (FAILURE);
	if (ft_is_empty_quotes_error(prompt) == 127)
		return (127);
	return (SUCCESS);
}
