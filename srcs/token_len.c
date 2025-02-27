/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:37:31 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/27 17:32:18 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_doll_len(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i + len] && str[i + len] != ' '
		&& str[i + len] != '\"' && str[i] != '\''
		&& (str[i + len] != '$' || len == 0))
		len ++;
	return (len);
}

int	ft_dquoted_len(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i + len] && str[i + len] != '\"' && !ft_is_doll(str, i))
		len ++;
	return (len);
}

int	ft_squoted_len(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i + len] && str[i + len] != '\'')
		len ++;
	return (len);
}

int	ft_strlen_content(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i] && ft_is_operand(str, i) == 0
		&& ft_is_doll(str, i) == 0 && ft_is_in_quotes(str, i) == 0
		&& ft_isspace(str[i]) == 0)
	{
		i++;
		len ++;
	}
	return (len);
}
