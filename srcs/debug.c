/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:40:07 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/06 14:14:01 by lmatkows         ###   ########.fr       */
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

	(void)env;
	temp = list;
	printf("nb args : %d\n", ft_nb_str(list));
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
		printf("is double quoted : %d %d\n", temp->dq_start, temp->dq_end);
		printf("need for space after : %d\n\n", temp->print_space_after);
		temp = temp->next;
	}
}

void	ft_print_chev(char **chev)
{
	int	i;

	i = 0;
	while (chev[i])
	{
		printf("chev %d : %s\n", i, chev[i]);
		i++;
	}
}

void	ft_print_info_cmd_list(int nb_cmd, t_cmd **list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("add cmd_list : %p\n", list);
	printf("nb cmd : %d\n\n", nb_cmd);
	while (i < nb_cmd)
	{
		j = 0;
		while (((list[i])->arg[j]))
		{
			printf("arg %d = %s\n", j, (list[i])->arg[j]);
			j++;
		}
		printf("nb_args : %d\n", j);
		printf("fd in is def : %d\n", list[i]->fd_in.is_def);
		printf("fd out is def : %d\n", list[i]->fd_out.is_def);
		printf("fd in : %d\n", list[i]->fd_in.fd);
		printf("fd out : %d\n", list[i]->fd_out.fd);
		printf("fneed pipe in : %d\n", list[i]->need_pipe_in);
		printf("fneed pipe out : %d\n", list[i]->need_pipe_out);
		printf("\n\n");
		i++;
	}
}
