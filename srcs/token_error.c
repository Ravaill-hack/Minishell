/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:30:44 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/03/09 12:40:34 by lmatkows         ###   ########.fr       */
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
/*
int	ft_build_redir_string(t_cmd *node, int i)
{
	char	*tmp;
	char	*redir;

	redir = NULL;
	while (node->raw[i] && ((node->raw[i][0] == '<' && !node->raw[i][1])
		|| (node->raw[i][0] == '>' && !node->raw[i][1])
		|| (node->raw[i][0] == '<' && node->raw[i][1] == '<' && !node->raw[i][2])
		|| (node->raw[i][0] == '>' && node->raw[i][1] == '>' && !node->raw[i][2])))
	{
		tmp = node->raw[i];
		redir = ft_strjoin(redir, tmp);
		if (tmp != redir)
			free(tmp);
		i++;
	}
	return (redir);
}
*/

int	ft_token_redir_error(t_cmd *node, int i)
{
	char	*str;
	//char	*tmp;

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
		while (prompt[i])
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
		while (prompt[i])
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
	// if (((prompt[0] == 34 && prompt[1] == 34)
	// 	|| (prompt[0] == '\'' && prompt[1] == '\'')) && !prompt[2])
	// {
	// 	ft_putstr_fd("Command \'\' not found.\n", 2);
	// 	return (127);	
	// }
	// return (SUCCESS);
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
