/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:09:21 by juduchar          #+#    #+#             */
/*   Updated: 2025/03/07 19:02:13 by lmatkows         ###   ########.fr       */
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

int	ft_nb_str(t_token_list *list)
{
	int	res;

	res = 0;
	while (list && (list->type != PIPE))
	{
		if ((list->print_space_after == 1)
			|| (list->next && list->next->type == PIPE)
			|| !(list->next)
			|| (list->next->type >= 0 && list->next->type <= 3)
			|| (list->type == DOLL))
			res ++;
			
		/*if (list->print_space_after == 0 && list->next
			&& (list->next->type >= 0 && list->next->type <= 3))
			res --;*/
		if (list->type == DOLL && (!list->val || !list->val[0] || (list->prev && (list->prev->type == DOLL /*&& list->prev->val*/))))
			res --;
		if (list->type == CONTENT && (list->prev && list->prev->print_space_after == 0 && list->prev->type == DOLL))
			res --;
		list = list->next;
	}
	//ft_putnbr_fd(res, 1);
	//ft_putchar_fd('\n', 1);
	return (res);
}

// (list->type == DOLL && list->prev && list->prev->type != DOLL)
