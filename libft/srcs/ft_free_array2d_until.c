/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array2d_until.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:31:31 by juduchar          #+#    #+#             */
/*   Updated: 2025/02/05 22:33:17 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

// free a 2D array of ints until n (not included)
int	**ft_free_array2d_until(int **array2d, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(array2d[i]);
		i++;
	}
	free(array2d);
	return (NULL);
}
