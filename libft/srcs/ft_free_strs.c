/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:43:19 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/15 15:31:47 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

// free an array of strings
char	**ft_free_strs(char **strs)
{
	size_t	i;

	if (!strs)
		return (NULL);
	if (!*strs)
	{
		free(strs);
		return (NULL);
	}
	i = 0;
	while (strs[i])
	{
		ft_check_and_free((void **)&(strs[i]));
		i++;
	}
	free(strs);
	return (NULL);
}
