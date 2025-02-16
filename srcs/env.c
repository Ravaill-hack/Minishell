/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 10:31:57 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/16 10:32:29 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_modify_shlvl(char **matrix, int ind)
{
	int 	i;
	int		len;
	char	*shlvl;
	char	*nb_str;

	i = 0;
	while (ft_strncmp(matrix[i], "SHLVL=", 6) != 0)
		i++;
	if (!matrix[i])
		return (NULL);
	nb_str = ft_itoa(ft_atoi(&matrix[i][6]) + ind);
	if (!nb_str)
		return (NULL);
	len = ft_strlen(nb_str) + 6;
	shlvl = (char *)malloc((len + 1) * sizeof(char));
	if (!shlvl)
		return (free(nb_str), NULL);
	ft_strlcpy(shlvl, "SHLVL=", len + 1);
	ft_strlcat(shlvl, nb_str, len + 1);
	free(nb_str);
	free(matrix[i]);
	matrix[i] = shlvl;
	return (matrix);
}

