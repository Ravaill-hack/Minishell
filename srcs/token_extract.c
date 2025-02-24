/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_extract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:31:43 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/24 15:44:48 by lmatkows         ###   ########.fr       */
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

char	*ft_extract_doll(char *line, int *i)
{
	int		len;
	char	*str;
	int		j;

	len = ft_doll_len(line, *i);
	str = (char *)malloc((len + 1) * sizeof(char));
	j = 0;
	if (!str)
		return (NULL);
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
	title = (char *)malloc((ft_doll_len(str, *i) + 1) * sizeof(char));
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
