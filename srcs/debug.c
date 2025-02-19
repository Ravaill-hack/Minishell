/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:40:07 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/19 13:56:52 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_token_type(t_token_list *token)
{
	printf("token type : ");
	if (token->type == 0)
		printf("<\n\n");
	else if (token->type == 1)
		printf("<<\n\n");
	else if (token->type == 2)
		printf(">\n\n");
	else if (token->type == 3)
		printf(">>\n\n");
	else if (token->type == 4)
		printf("|\n\n");
	else if (token->type == 5)
		printf("new line\n\n");
	else if (token->type == 6)
		printf("content\n");
	else
		printf("error\n\n");
}

void	ft_print_info_list(t_token_list **list)
{
	t_token_list	*temp;

	temp = *list;
	printf("add liste : %p\n", list);
	while (temp)
	{
		printf("prev : %p\n", temp->prev);
		printf("self : %p\n", temp);
		printf("next : %p\n", temp->next);
		ft_print_token_type(temp);
		if (temp->type == CONTENT)
			printf("content : %s\n\n", temp->val);
		temp = temp->next;
	}
}
