/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:55:13 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/14 18:21:15 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_line_token	*ft_find_token_value(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
	if (ft_strncmp(&str[*i], ">", 1) == 0)
		return (S_GREAT);
}

t_token_list	*ft_last_token(t_token_list *token)
{
	while (token && token->next)
		token = token->next;
	return (token);
}

t_token_list	*ft_append_token(char *str, int *i, t_token_list **list)
{
	t_token_list	*token;

	token = (t_token_list *)malloc(sizeof(t_token_list));
	if (!token)
		return (NULL);
	token->val = ft_find_token_value(str, i);
	token->next = NULL;
	if (!(*list))
	{
		*list = token;
		token->prev = NULL;
	}
	else
		token->prev = ft_last_token(list);
		ft_last_token(list)->next = token;
	return (token);
}

t_token_list	**ft_create_token_list(char *str)
{
	t_token_list	**list;
	int				i;

	i = 0;
	list = (t_token_list **)malloc(sizeof(t_token_list *));
	if (!list)
		return (NULL);
	while (str[i] != '\0')
		ft_append_token(str, &i, list);
	return (list);
}
