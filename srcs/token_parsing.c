/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:55:13 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/25 21:13:10 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_list	*ft_deal_dquoted(char *line, int *i, t_token_list **list)
{
	t_token_list	*res;
	int				tour;

	res = NULL;
	tour = 0;
	if (line[*i] == '\"')
		(*i)++;
	while (line[*i] && line[*i] != '\"')
	{
		if (ft_is_doll(line, *i))
			res = ft_append_doll(line, i, list);
		else
			res = ft_append_dquoted(line, i, list);
		if (tour == 0)
			res->dq_start = 1;
		if (line[*i] == '\"')
			res->dq_end = 1;
		if (!res)
			return (NULL);
		tour ++;
	}
	if (line[*i] == '\"')
		(*i)++;
	return (*list);
}

int	ft_append_tokens(char *line, t_token_list **list)
{
	int				i;
	t_token_list	*err;

	i = 0;
	err = *list;
	while (line[i])
	{
		ft_skip_spaces(line, &i, *list);
		if (ft_is_operand(line, i) == 1)
			err = ft_append_operand(line, &i, list);
		else if (ft_is_in_dquotes(line, i))
			err = ft_deal_dquoted(line, &i, list);
		else if (ft_is_in_squotes(line, i))
			err = ft_append_squoted(line, &i, list);
		else if (ft_is_doll(line, i))
			err = ft_append_doll(line, &i, list);
		else
			err = ft_append_content(line, &i, list);
		if (!err)
			return (1);
	}
	return (0);
}

t_token_list	**ft_build_token_list(char *line)
{
	t_token_list	**list;
	int				err;

	if (ft_quote_error(line) == 1)
		return (NULL);
	list = (t_token_list **)ft_calloc(1, sizeof(t_token_list *));
	if (!list)
		return (NULL);
	*list = NULL;
	err = ft_append_tokens(line, list);
	if (err == 1)
	{
		ft_free_list(list);
		return (NULL);
	}
	return (list);
}

int	ft_parse_line(t_var *var)
{
	var->token_list = ft_build_token_list(var->line);
	if (!var->token_list)
		return (FAILURE);
	var->cmd = ft_build_cmd_list(var);
	if (!var->cmd)
		return (FAILURE);
	return (SUCCESS);
}
