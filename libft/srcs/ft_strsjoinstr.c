/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoinstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 21:47:22 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/19 21:47:39 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsjoinstr(char **strs, char *str)
{
	char	**new_strs;
	int		strs_len;

	strs_len = ft_strslen(strs);
	new_strs = (char **)ft_calloc(sizeof(char *), (strs_len + 2));
	if (!new_strs)
		return (NULL);
	ft_strslcpy(new_strs, strs, strs_len + 1);
	new_strs[strs_len] = ft_strdup(str);
	if (!new_strs[strs_len])
		return (ft_free_strs(new_strs), NULL);
	new_strs[strs_len + 1] = NULL;
	free(strs);
	return (new_strs);
}
