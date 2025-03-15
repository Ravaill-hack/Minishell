/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:36:11 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/03/15 11:07:13 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE //

#include "minishell.h"

t_line_token	ft_find_token_type(char *str, int i)
{
	if (str[i] == '>' && str[i + 1] != '>')
		return (S_GREAT);
	else if (str[i] == '<' && str[i + 1] != '<')
		return (S_LESS);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (D_GREAT);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (D_LESS);
	else if (str[i] == '|')
		return (PIPE);
	else if (ft_is_doll(str, i))
		return (DOLL);
	else
		return (CONTENT);
}

t_token_list	*ft_last_token(t_token_list *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
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

void	ft_skip_spaces(char *str, int *i, t_token_list *list)
{
	t_token_list	*last;

	last = ft_last_token(list);
	if (last && ft_isspace(str[*i]) == 1
		&& !(last->type >= 0 && last->type <= 3))
		last->psa = 1;
	while (ft_isspace(str[*i]) == 1)
		(*i)++;
}

int	ft_cond_token_synt(t_token_list *node)
{
	if (node->type == 6 && node->val[0] == '.' && !node->val[1]
		&& (node->psa == 1 || !node->next || node->next->type <= 3))
		return (1);
	return (0);
}
