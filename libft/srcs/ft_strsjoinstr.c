/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoinstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 21:47:22 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/27 12:55:53 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	**ft_strsjoinstr(char **strs, char *str)
{
	char	**new_strs;
	int		strs_len;

	strs_len = ft_strslen(strs);
	new_strs = (char **)ft_calloc(sizeof(char *), (strs_len + 2));
	if (!new_strs)
		return (NULL);
	ft_strslcpy(&new_strs, strs, strs_len + 1);
	new_strs[strs_len] = ft_strdup(str);
	if (!new_strs[strs_len])
		return (ft_free_strs(new_strs), NULL);
	new_strs[strs_len + 1] = NULL;
	ft_free_strs(strs);
	return (new_strs);
}
