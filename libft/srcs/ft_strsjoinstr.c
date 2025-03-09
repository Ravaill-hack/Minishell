/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoinstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 21:47:22 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/03/09 14:56:42 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	**ft_strsjoinstr(char **strs, char *str)
{
	char	**new_strs;
	int		strs_len;

	strs_len = ft_strslen(strs);
	new_strs = (char **)ft_calloc((strs_len + 2), sizeof(char *));
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
