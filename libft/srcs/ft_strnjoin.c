/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 08:40:16 by juduchar          #+#    #+#             */
/*   Updated: 2025/01/13 08:37:39 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char *dst, const char *src,
	size_t dst_len, size_t src_len)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char *) malloc((dst_len + src_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	if (dst)
	{
		while (i < dst_len)
		{
			str[i] = dst[i];
			i++;
		}
		free(dst);
	}
	j = 0;
	while (j < src_len)
		str[i++] = src[j++];
	str[i] = '\0';
	return (str);
}
