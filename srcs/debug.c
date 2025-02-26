/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:40:07 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/26 08:42:46 by lmatkows         ###   ########.fr       */
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
	else if (token->type == 7)
		printf("$\n");
	else
		printf("error\n\n");
}

void	ft_print_info_list(t_token_list *list, char **env)
{
	t_token_list	*temp;

	temp = list;
	printf("nb args : %d\n", ft_nb_str(list, env));
	printf("add liste : %p\n", list);
	while (temp)
	{
		printf("prev : %p\n", temp->prev);
		printf("self : %p\n", temp);
		printf("next : %p\n", temp->next);
		ft_print_token_type(temp);
		if (temp->type == CONTENT)
			printf("content : %s\n", temp->val);
		else if (temp->type == DOLL)
			printf("content : %s\n", temp->val);
		printf("need for space after : %d\n\n", temp->print_space_after);
		temp = temp->next;
	}
}

void	ft_print_info_cmd_list(int nb_cmd, t_cmd **list)
{
	int	i;

	i = 0;
	printf("add cmd_list : %p\n", list);
	while (i < nb_cmd)
	{
		ft_print_strs((list[i])->arg);
		printf("\n\n");
		i++;
	}
}
