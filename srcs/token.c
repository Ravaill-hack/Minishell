/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:55:13 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/18 10:21:49 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_line_token	ft_find_token_type(char *str)
{
	if (ft_strncmp(str, ">", 1) == 0)
		return (S_GREAT);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (S_LESS);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (D_GREAT);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (D_LESS);
	else if (ft_strncmp(str, "|", 1) == 0)
		return (PIPE);
	else if (ft_strncmp(str, "(", 1) == 0)
		return (O_PAR);
	else if (ft_strncmp(str, ")", 1) == 0)
		return (C_PAR);
	else if (ft_strncmp(str, "||", 2) == 0)
		return (OR);
	else if (ft_strncmp(str, "&&", 2) == 0)
		return (AND);
	else
		return (CONTENT);
}

t_token_list	*ft_last_token(t_token_list *token)
{
	while (token && token->next)
		token = token->next;
	return (token);
}

t_token_list	*ft_append_token(char *word, t_token_list **list)
{
	t_token_list	*token;

	token = (t_token_list *)malloc(sizeof(t_token_list));
	if (!token)
		return (NULL);
	token->token = ft_find_token_type(word);
	token->next = NULL;
	if (!(*list))
	{
		*list = token;
		token->prev = NULL;
	}
	else
	{
		token->prev = ft_last_token(*list);
		ft_last_token(*list)->next = token;
	}
	return (token);
}

void	ft_free_list(t_token_list **list)
{
	t_token_list	*tmp;
	t_token_list	**add;

	add = list;
	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
	free(add);
}

t_token_list	**ft_build_token_list(char **split_line)
{
	t_token_list	**list;
	int				i;

	i = 0;
	list = (t_token_list **)malloc(sizeof(t_token_list *));
	if (!list)
		return (NULL);
	*list = NULL;
	while (split_line[i])
	{
		if (!ft_append_token(split_line[i], list))
			ft_free_list(list);
		i++;
	}
	return (list);
}
