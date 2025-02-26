/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:09:21 by juduchar          #+#    #+#             */
/*   Updated: 2025/02/26 09:51:27 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*temp;
	char	*res;

	temp = ft_strjoin(s1, s2);
	res = ft_strjoin(temp, s3);
	free(temp);
	return (res);
}

int	ft_nb_pipes(t_token_list *list)
{
	int	res;

	res = 0;
	while (list)
	{
		if (list->type == PIPE)
			res ++;
		list = list->next;
	}
	return (res);
}

int	ft_nb_dolls(t_token_list *list)
{
	int	res;

	res = 0;
	while (list)
	{
		if (list->type == DOLL)
			res ++;
		list = list->next;
	}
	return (res);
}

int	ft_nb_str(t_token_list *list, char **env)
{
	int	res;

	res = 0;
	while (list && (list->type == CONTENT || list->type == DOLL))
	{
		if (list->print_space_after == 1
			|| (list->next && (list->next->type != 6 && list->next->type != 7))
			|| !(list->next) /*|| (list->next && list->next->type == DOLL)*/)
		{
			res ++;
			if (list->type == DOLL 
				&& !ft_doll_var_exists(list->val, env)
				&& !ft_is_nb_exit(list->val + 1)
				&& (list->prev && list->prev->print_space_after == 1))
				res --;
		}
		list = list->next;
	}
	return (res);
}
