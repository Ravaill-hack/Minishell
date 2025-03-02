/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:50:39 by julien            #+#    #+#             */
/*   Updated: 2025/03/02 12:40:20 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsdup(char *const *strs)
{
	size_t	i;
	size_t	strs_len;
	char	**dup;

	i = 0;
	if (!strs)
		return (NULL);
	strs_len = ft_strslen(strs);
	dup = (char **)ft_calloc((strs_len + 1), sizeof(char *));
	if (!dup)
		return (NULL);
	while (i < strs_len)
	{
		dup[i] = ft_strdup(strs[i]);
		if (dup[i] == NULL)
			return (ft_free_strs_until(dup, i));
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
