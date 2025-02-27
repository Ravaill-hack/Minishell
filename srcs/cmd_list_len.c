/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:57:12 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/27 17:17:10 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen_nb(int n)
{
	size_t	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

int	ft_len_new_array(char **old)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (old[i])
	{
		if (old[i][0] != '<' && old[i][0] != '>')
			len ++;
		i++;
	}
	return (len);
}

int	ft_find_special_len(t_token_list *node, char **env)
{
	int	len;
	int	len_doll;

	len = 0;
	len_doll = 0;
	while (node
		&& (node->print_space_after == 0
			|| node->type != CONTENT
			|| node->type != DOLL))
	{
		if (node->type == DOLL)
		{
			len_doll = ft_doll_val_len(node->val, env);
			if (len_doll == 0)
				node = node->next;
			else
				len += len_doll;
		}
		else if (node->type == CONTENT)
			len += ft_strlen((const char *)node->val);
		node = node->next;
	}
	return (len);
}

int	ft_doll_val_len(char *doll, char **env)
{
	int		len;
	char	*ptr;

	len = 0;
	ptr = ft_extract_env_value_from_key(env, &(doll[1]));
	while (ptr && ptr[len])
		len ++;
	return (len);
}
