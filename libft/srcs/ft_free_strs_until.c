/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strs_until.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:56:16 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/02 12:38:16 by julien           ###   ########.fr       */
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
	else
	{
		while (i < n)
		{
			free(strs[i]);
			i++;
		}
	}
	if (strs)
		free(strs);
	return (NULL);
}
