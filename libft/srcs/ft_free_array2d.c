/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array2d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:36:08 by juduchar          #+#    #+#             */
/*   Updated: 2025/02/05 22:32:11 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

// free a 2D array of ints
void	ft_free_array2d(int **array2d)
{
	size_t	i;

	i = 0;
	while (array2d[i])
	{
		free(array2d[i]);
		i++;
	}
	free(array2d);
}
