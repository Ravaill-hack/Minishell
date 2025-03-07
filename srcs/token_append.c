/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:26:37 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/03/07 16:54:34 by lmatkows         ###   ########.fr       */
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
	token->val = ft_extract_content(line, i);
	token->dq_end = 0;
	token->dq_start = 0;
	token->sq = 0;
	token->print_space_after = 0;
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
	token->dq_end = 0;
	token->dq_start = 0;
	token->sq = 1;
	token->print_space_after = 0;
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
	token->print_space_after = 0;
	token->dq_start = 0;
	token->dq_end = 0;
	token->sq = 0;
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

t_token_list	*ft_append_doll(char *line, int *i, t_token_list **list, int x)
{
	t_token_list	*token;

	token = (t_token_list *)ft_calloc(1, sizeof(t_token_list));
	if (!token)
		return (NULL);
	token->val = ft_extract_doll(line, i, x);
	token->print_space_after = 0;
	token->dq_start = 0;
	token->dq_end = 0;
	token->sq = 0;
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
	token->print_space_after = 0;
	token->dq_end = 0;
	token->dq_start = 0;
	if (token->type == 1 || token->type == 3)
		(*i) += 2;
	else if (token->type == 4 || token->type == 0 || token->type == 2)
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
