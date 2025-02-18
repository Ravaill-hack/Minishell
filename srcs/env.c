/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 10:31:57 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/18 13:18:56 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_modify_shlvl(char **matrix, int ind)
{
	int 	i;
	char	*shlvl;
	char	*nb_str;

	if (!matrix)
		return (NULL);
	i = 0;
	while (ft_strncmp(matrix[i], "SHLVL=", 6) != 0)
		i++;
	if (!matrix[i])
		return (NULL);
	nb_str = ft_itoa(ft_atoi(&matrix[i][6]) + ind);
	if (!nb_str)
		return (NULL);
	shlvl = ft_strjoin("SHLVL=", nb_str);
	if (!shlvl)
		return (free(nb_str), NULL);
	free(nb_str);
	free(matrix[i]);
	matrix[i] = shlvl;
	return (matrix);
}

