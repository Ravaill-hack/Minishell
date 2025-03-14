/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:31:57 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/05 22:12:02 by julien           ###   ########.fr       */
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

t_token_list	*ft_go_to_next_node(t_token_list *node)
{
	if (node)
		node = node->next;
	else
		return (NULL);
	while (node)
	{
		if (node->prev
			&& ((node->prev->print_space_after == 1 && node->type != PIPE)
				|| (node->prev->print_space_after == 0
					&& (node->type >= 0 && node->type <= 3))))
			break ;
		node = node->next;
	}
	return (node);
}
