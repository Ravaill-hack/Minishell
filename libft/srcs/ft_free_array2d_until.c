/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array2d_until.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:31:31 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/15 15:31:35 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

// free a 2D array of ints until n (not included)
int	**ft_free_array2d_until(int **array2d, size_t n)
{
	size_t	i;

	i = 0;
	if (!array2d)
		return (NULL);
	while (i < n)
	{
		ft_check_and_free((void **)(&(array2d[i])));
		i++;
	}
	if (array2d)
		free(array2d);
	return (NULL);
}
