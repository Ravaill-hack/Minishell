/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:43:31 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/18 10:28:09 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(char **matrix, int ind)
{
	int	i;

	i = 0;
	while (i < ind)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	ft_nb_lines(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

char	**ft_chartab_dup(char **matrix)
{
	char	**res;
	int		leni;
	int		i;

	i = 0;
	if (!matrix)
		return (NULL);
	leni = ft_nb_lines(matrix);
	res = (char **)malloc((leni + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < leni)
	{
		res[i] = ft_strdup(matrix[i]);
		if (res[i] == NULL)
		{
			ft_free_tab(res, i);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	ft_clear_and_free_all(t_var var)
{
	if (var.env)
		ft_free_strs(var.env);
	rl_clear_history();
	ft_enable_echoctl();
}