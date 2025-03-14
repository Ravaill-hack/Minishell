/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:16:10 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/06 17:25:42 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_list	*ft_deal_dquoted(char *line, int *i, t_token_list **list, int x)
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
			res = ft_append_doll(line, i, list, x);
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
	if (((prompt[0] == 34 && prompt[1] == 34)
		|| (prompt[0] == '\'' && prompt[1] == '\'')) && !prompt[2])
	{
		ft_putstr_fd("Command \'\' not found.\n", 2);
		return (FAILURE);	
	}
	var->token_list = ft_build_token_list(prompt, var->exit_nb);
	if (!var->token_list)
		return (FAILURE);
	//ft_print_info_list(*(var->token_list), var->env);
	ft_expand_dolls(*(var->token_list), var);
	var->cmd = ft_build_cmd_list(var, shell);
	if (!var->cmd)
		return (FAILURE);
	return (SUCCESS);
}
