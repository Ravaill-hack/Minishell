/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array2d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:36:08 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/12 16:38:37 by lmatkows         ###   ########.fr       */
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
	array2d = NULL;
}
