/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:55:13 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/27 09:48:42 by lmatkows         ###   ########.fr       */
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

int	ft_doll_var_exists(char *str, char **env)
{
	int	i;

	i = 0;
	
	while (env[i])
	{
		if (ft_strncmp(str, env[i], ft_strlen(str)) == 0
			&& env[i][ft_strlen(str)] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_doll_val_len(char *doll, char **env)
{
	int		len;
	char	*ptr;

	len = 0;
	ptr = ft_extract_env_value_from_key(env, &(doll[1]));
	while (ptr && ptr[len])
		len ++;
	return (len);
}

char	*ft_exit_nb_join(char *str, t_var *var)
{
	char	*nb;
	char	*joined_str;

	nb = ft_itoa(var->exit_nb);
	joined_str = ft_strjoin(nb, str);
	free(nb);
	return (joined_str);
}

char	*ft_replace_doll(char *str, t_var *var)
{
	if (!str[1])
		return (str);
	if (str[1] == '?' && !str[2])
		return (ft_itoa(var->exit_nb));
	if (str[1] == '?' && str[2])
		return (ft_exit_nb_join(&str[2], var));
	if (ft_doll_var_exists(str + 1, var->env))
		return (ft_extract_env_value_from_key(var->env, str + 1));
	else
		return (ft_strdup("")); //NULL ou chaine vide?
}

int	ft_expand_dolls(t_token_list *list, t_var *var)
{
	char	*tmp;

	tmp = NULL;
	while (list)
	{
		if (list->type == DOLL)
		{
			tmp = list->val;
			list->val = ft_replace_doll(list->val, var);
			if (tmp != list->val)
				free(tmp);
		}
		list = list->next;
	}
	return (1);
}

int	ft_parse_line(t_var *var)
{
	var->token_list = ft_build_token_list(var->line);
	if (!var->token_list)
		return (FAILURE);
	ft_expand_dolls(*(var->token_list), var);
	/*var->cmd = ft_build_cmd_list(var);
	if (!var->cmd)
		return (FAILURE);*/
	return (SUCCESS);
}
