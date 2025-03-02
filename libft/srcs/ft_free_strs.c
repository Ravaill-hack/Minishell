/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:43:19 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/02 11:26:11 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

// free an array of strings
void	ft_free_strs(char **strs)
{
	size_t	i;

	if (!strs)
		return ;
	if (!*strs)
	{
		free(strs);
		return ;
	}
	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
