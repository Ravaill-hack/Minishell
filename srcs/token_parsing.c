/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:16:10 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/10 19:57:00 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE //

#include "minishell.h"

void	ft_handle_dquoted_content(char *line, int *i,
		t_token_list **list, int x)
{
	int				tour;
	t_token_list	*res;

	tour = 0;
	while (line[*i] && line[*i] != '\"')
	{
		if (ft_is_doll(line, *i))
			res = ft_append_doll(line, i, list, x);
		else
			res = ft_append_dquoted(line, i, list);
		if (tour == 0)
			res->dq_start = 1;
		if (line[*i] == '\"')
			res->dq_end = 1;
		if (!res)
			return ;
		tour++;
	}
}

t_token_list	*ft_deal_dquoted(char *line, int *i, t_token_list **list, int x)
{
	t_token_list	*res;

	res = NULL;
	if (line[*i] == '\"' && line[*i + 1] == '\"')
	{
		(*i)++;
		res = ft_append_dquoted(line, i, list);
		res->dq_start = 1;
		res->dq_end = 1;
		(*i)++;
		return (res);
	}
	if (line[*i] == '\"')
		(*i)++;
	ft_handle_dquoted_content(line, i, list, x);
	if (line[*i] == '\"')
		(*i)++;
	return (*list);
}

int	ft_append_tokens(char *line, t_token_list **list, int nb_x)
{
	int				i;
	t_token_list	*err;

	i = 0;
	err = *list;
	while (line[i])
	{
		ft_skip_spaces(line, &i, *list);
		if (!line[i])
			return (1);
		if (ft_is_operand(line, i) == 1)
			err = ft_append_operand(line, &i, list);
		else if (ft_is_in_dquotes(line, i))
			err = ft_deal_dquoted(line, &i, list, nb_x);
		else if (ft_is_in_squotes(line, i))
			err = ft_append_squoted(line, &i, list);
		else if (ft_is_doll(line, i))
			err = ft_append_doll(line, &i, list, nb_x);
		else
			err = ft_append_content(line, &i, list);
		if (!err)
			return (1);
	}
	return (0);
}

t_token_list	**ft_build_token_list(char *line, int nb_x)
{
	t_token_list	**list;
	int				err;

	if (ft_quote_error(line) == 1)
		return (NULL);
	list = (t_token_list **)ft_calloc(1, sizeof(t_token_list *));
	if (!list)
		return (NULL);
	*list = NULL;
	err = ft_append_tokens(line, list, nb_x);
	if (err == 1)
	{
		ft_free_list(list);
		return (NULL);
	}
	return (list);
}

int	ft_parse_line(t_var *var, char *prompt, t_shell *shell)
{
	int	status;

	status = ft_is_error_parsing(prompt);
	if (status != 0)
		return (status);
	var->token_list = ft_build_token_list(prompt, var->exit_nb);
	if (!var->token_list)
		return (FAILURE);
	ft_expand_dolls(*(var->token_list), var);
	var->cmd = ft_build_cmd_list(var, shell);
	if (!var->cmd)
		return (FAILURE);
	return (SUCCESS);
}
