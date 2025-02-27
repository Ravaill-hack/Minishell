/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strs_until.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:56:16 by juduchar          #+#    #+#             */
/*   Updated: 2025/02/27 18:09:18 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

// free an array of strings until n (not included)
char	**ft_free_strs_until(char **strs, int n)
{
	int	i;

	i = 0;
	if (n == -1)
	{
		while (strs[i])
		{
			free(strs[i]);
			i++;
		}
	}
	while (i < n)
	{
		free(strs[i]);
		i++;
	}
	
	free(strs);
	return (NULL);
}
