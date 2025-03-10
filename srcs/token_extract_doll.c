/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_extract_doll.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:31:43 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/03/10 19:47:06 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE //

#include "minishell.h"

char	*ft_handle_question_mark(char *str, int i, int j, char *line)
{
	int	nb_dq;

	nb_dq = 0;
	while (line[i] && line[i] != ' '
		&& (line[i] != '\"' && nb_dq == 0)
		&& line[i] != '\'' && (line[i] != '$' || j == 0))
	{
		if (line[i] == '\"')
		{
			nb_dq = 1;
			i++;
		}
		str[j] = line[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_extract_doll(char *line, int *i, int nb_x)
{
	int		len;
	char	*str;
	int		j;
	int		nb_dq;

	nb_dq = 0;
	len = ft_doll_len(line, *i, nb_x);
	str = (char *)ft_calloc((len + 1), sizeof(char));
	j = 0;
	if (!str)
		return (NULL);
	if (line[*i + 1] == '?' && line[*i + 2] == '\"')
		return (ft_handle_question_mark(str, j, line, *i));
	while (line[*i] && line[*i] != '\"' && line[*i] != ' '
		&& line[*i] != '\'' && (line[*i] != '$' || j == 0))
	{
		str[j] = line[*i];
		j++;
		(*i)++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_extract_title_doll(char *str, int *i)
{
	int		j;
	char	*title;

	j = 0;
	title = (char *)malloc((ft_doll_len(str, *i, 0) + 1) * sizeof(char));
	if (!title)
		return (NULL);
	while (str[*i] && str[*i] != ' ' && str[*i] != '\"'
		&& (str[*i] != '$' || j == 0))
	{
		title[j] = str[*i];
		j++;
		(*i)++;
	}
	if (str[*i] != '\"')
		(*i)++;
	title[j] = '\0';
	return (title);
}
