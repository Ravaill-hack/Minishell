/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:37:31 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/03/10 11:08:03 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_doll_len(char *str, int i, int nb_ex)
{
	int	len;
	int	nb_dq;

	len = 0;
	nb_dq = 0;
	(void) nb_ex;
	while (str[i + len] && str[i + len] != ' '
		&& str[i + len] != '\"' && str[i] != '\''
		&& (str[i + len] != '$' || len == 0))
		len ++;
	if (str[i + 1] == '?' && str[i + 2] == '\"')
	{
		len = 0;
		while (str[i + len] && str[i + len] != ' '
			&& (str[i + len] != '\"' && nb_dq == 0)
			&& str[i] != '\'' && (str[i + len] != '$' || len == 0))
		{
			if (str[i + len] == '\"')
			{
				nb_dq = 1;
				len--;
			}
			len ++;
		}
	}
	return (len);
}

int	ft_dquoted_len(char *str, int i)
{
	int	len;

	len = 0;
	if (str[i] == '\"')
		return (0);
	while (str[i + len] && str[i + len] != '\"' && !ft_is_doll(str, i))
		len ++;
	return (len);
}

int	ft_squoted_len(char *str, int i)
{
	int	len;

	len = 0;
	i++;
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

int	ft_exit_nb_len(int nb_exit)
{
	char	*tmp;
	int		len;

	tmp = ft_itoa(nb_exit);
	if (!tmp)
		return (FAILURE);
	len = ft_strlen(tmp);
	free(tmp);
	return (len);
}
