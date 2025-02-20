/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlscpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 21:44:58 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/20 17:36:59 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strslcpy(char ***dst, char *const *src, size_t size)
{
	size_t	i;
	size_t	srcs_len;

	if (!dst || !src)
		return (0);
	srcs_len = ft_strslen(src);
	if (size == 0)
		return (srcs_len);
	i = 0;
	while (src[i] && i < size - 1)
	{
		(*dst)[i] = ft_strdup(src[i]);
		i++;
	}
	(*dst)[i] = NULL;
	return (srcs_len);
}
