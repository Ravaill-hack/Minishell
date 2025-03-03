/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array2d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:36:08 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/03 18:48:36 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

// free a 2D array of ints
void	ft_free_array2d(int **array2d)
{
	size_t	i;

	i = 0;
	if (!array2d)
		return ;
	while (array2d[i])
	{
		free(array2d[i]);
		i++;
	}
	free(array2d);
}
