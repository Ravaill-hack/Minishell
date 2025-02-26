/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:37:31 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/26 19:53:45 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_doll_len(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i + len] && str[i + len] != ' '
		&& str[i + len] != '\"'&& str[i] != '\'' 
		&& (str[i + len] != '$' || len == 0))
		len ++;
	return (len);
}

int	ft_dquoted_len(char *str, int i)
{
	int	len;

	len = 0;
	if (str[i] == '\"')
		i++;
	while (str[i + len] != '\"' || (str[i + len] == '\"' && str[i + len + 1] == '\"'))
	{
		if (str[i + len] == '\"')
			i += 2;
		else
			len++;
	}
	return (len);
}

int	ft_squoted_len(char *str, int i)
{
	int	len;

	len = 0;
	if (str[i] == '\'')
		i++;
	while (str[i + len] != '\'' || (str[i + len] == '\'' && str[i + len + 1] == '\''))
	{
		if (str[i + len] == '\'')
			i += 2;
		else
			len++;
	}
	return (len);
}

int	ft_strlen_content(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i] && ft_is_operand(str, i) == 0 && ft_isspace(str[i]) == 0)
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
			{
				len++;
				i++;
			}
			i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
			{
				len++;
				i++;
			}
			i++;			
		}
		else
		{
			i++;
			len ++;		
		}
	}
	return (len);
}
