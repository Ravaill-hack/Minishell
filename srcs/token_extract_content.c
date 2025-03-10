/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_extract_content.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:44:02 by julien            #+#    #+#             */
/*   Updated: 2025/03/10 19:44:25 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_extract_content(char *line, int *i)
{
	int		len;
	char	*str;
	int		j;

	len = ft_strlen_content(line, *i);
	str = (char *)malloc((len + 1) * sizeof(char));
	j = 0;
	if (!str)
		return (NULL);
	while (line[*i] && ft_is_operand(line, *i) == 0
		&& ft_is_doll(line, *i) == 0 && ft_is_in_quotes(line, *i) == 0
		&& ft_isspace(line[*i]) == 0)
	{
		str[j] = line[*i];
		j++;
		(*i)++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_extract_sq_content(char *line, int *i)
{
	int		len;
	char	*str;
	int		j;

	len = ft_squoted_len(line, *i);
	str = (char *)malloc((len + 1) * sizeof(char));
	j = 0;
	if (!str)
		return (NULL);
	(*i)++;
	while (line[*i] != '\'')
	{
		str[j] = line[*i];
		j++;
		(*i)++;
	}
	(*i)++;
	str[j] = '\0';
	return (str);
}

char	*ft_extract_dq_content(char *line, int *i)
{
	int		len;
	char	*str;
	int		j;

	len = ft_dquoted_len(line, *i);
	str = (char *)malloc((len + 1) * sizeof(char));
	j = 0;
	if (!str)
		return (NULL);
	while (line[*i] && line[*i] != '\"' && !ft_is_doll(line, *i))
	{
		str[j] = line[*i];
		j++;
		(*i)++;
	}
	str[j] = '\0';
	return (str);
}
