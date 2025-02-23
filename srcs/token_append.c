/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:26:37 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/23 18:10:01 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_list	*ft_append_content(char *line, int *i, t_token_list **list)
{
	t_token_list	*token;

	token = (t_token_list *)ft_calloc(1, sizeof(t_token_list));
	if (!token)
		return (NULL);
	token->type = CONTENT;
	if (ft_is_in_dquotes(line, *i))
		token->val = ft_extract_dq_content(line, i);
	else
		token->val = ft_extract_content(line, i);
	token->next = NULL;
	if (!(token->val))
		return (NULL);
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

t_token_list	*ft_append_squoted(char *line, int *i, t_token_list **list)
{
	t_token_list	*token;

	token = (t_token_list *)ft_calloc(1, sizeof(t_token_list));
	if (!token)
		return (NULL);
	token->type = CONTENT;
	token->val = ft_extract_sq_content(line, i);
	token->next = NULL;
	if (!(token->val))
		return (NULL);
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

t_token_list	*ft_append_dquoted(char *line, int *i, t_token_list **list)
{
	t_token_list	*token;

	token = (t_token_list *)ft_calloc(1, sizeof(t_token_list));
	if (!token)
		return (NULL);
	token->val = ft_extract_dq_content(line, i);
	token->type = CONTENT;
	token->next = NULL;
	if (!(token->val))
		return (NULL);
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

t_token_list	*ft_append_doll(char *line, int *i, t_token_list **list)
{
	t_token_list	*token;

	token = (t_token_list *)ft_calloc(1, sizeof(t_token_list));
	if (!token)
		return (NULL);
	token->val = ft_extract_doll(line, i);
	token->type = DOLL;
	token->next = NULL;
	if (!(token->val))
		return (NULL);
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

t_token_list	*ft_append_operand(char *line, int *i, t_token_list **list)
{
	t_token_list	*token;

	token = (t_token_list *)ft_calloc(1, sizeof(t_token_list));
	if (!token)
		return (NULL);
	token->type = ft_find_token_type(line, *i);
	if (token->type == D_LESS || token->type == D_GREAT)
		(*i) += 2;
	else if (token->type == PIPE || token->type == S_LESS
		|| token->type == S_GREAT)
		(*i) += 1;
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
