/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:28:56 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/23 18:13:00 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_doll(char *str, int i)
{
	if (ft_is_in_squotes(str, i) == 1)
		return (0);
	else if (str[i] == '$')
	{
		if (str[i + 1]
			&& !ft_strchr("~'!@#%^&*+-()[]{}|;:\',<>/\\", str[i +1]))
			return (1);
	}
	return (0);
}

int	ft_is_operand(char *str, int i)
{
	if (str[i] == '>' || str[i] == '<' || str[i] == '|')
		return (1);
	return (0);
}

int	ft_is_in_squotes(char *line, int ind)
{
	int	i;
	int	ns;
	int	nd;

	i = 0;
	ns = 0;
	nd = 0;
	while (i <= ind)
	{
		if (line[i] == '\'' && nd == 0)
			ns = !ns;
		else if (line[i] == '\"' && ns == 0)
			nd = !nd;
		i++;
	}
	if (ns != 0)
		return (1);
	return (0);
}

int	ft_is_in_dquotes(char *line, int ind)
{
	int	i;
	int	ns;
	int	nd;

	i = 0;
	ns = 0;
	nd = 0;
	while (i <= ind)
	{
		if (line[i] == '\'' && nd == 0)
			ns = !ns;
		else if (line[i] == '\"' && ns == 0)
			nd = !nd;
		i++;
	}
	if (nd != 0)
		return (1);
	return (0);
}

int	ft_is_in_quotes(char *line, int ind)
{
	if (ft_is_in_dquotes(line, ind) || ft_is_in_squotes(line, ind))
		return (1);
	return (0);
}
