/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:31:57 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/08 21:54:41 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_epure_args_array(char **old)
{
	int		len;
	char	**new_array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_len_new_array(old);
	new_array = (char **)malloc((len + 1) * sizeof(char *));
	if (!new_array)
		return (NULL);
	while (old[i])
	{
		if (old[i][0] != '<' && old[i][0] != '>')
		{
			new_array[j] = ft_strdup(old[i]);
			if (!new_array[j])
				return (ft_free_strs_until(new_array, j), NULL);
			j++;
		}
		i++;
	}
	new_array[j] = NULL;
	return (new_array);
}

