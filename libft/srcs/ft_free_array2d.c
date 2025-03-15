/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array2d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:36:08 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/15 16:34:46 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

// free a 2D array of ints
int	**ft_free_array2d(int **array2d)
{
	size_t	i;

	i = 0;
	if (!array2d)
		return (NULL);
	while (array2d[i])
	{
		ft_check_and_free((void **)(&(array2d[i])));
		i++;
	}
	if (array2d)
		free(array2d);
	return (NULL);
}
