/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:55:13 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/21 14:11:05 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_doll(char *str, int i)
{
	if (ft_is_in_squotes(str, i) == 1)
		return (0);
	else if (str[i] == '$')
	{
		if (str[i + 1]
			&& !ft_strchr("~'!@#%^&*+-()[]{}|;:\',<>/\\", str[i +1]))
		return (1);
	}
	return (0);
}

int	ft_is_in_squotes(char *line, int ind)
{
	int	i;
	int	ns;
	int	nd;

	i = 0;
	ns = 0; // 1 = open quote ; 0 = closed quote
	nd = 0; // 1 = open quote ; 0 = closed quote
	while (i <= ind)
	{
		if (line[i] == '\'' && nd == 0)
			ns = !ns;
		else if (line[i] == '\"' && ns == 0)
			nd = !nd;
		i++;
	}
	if (ns != 0)
		return (1);
	return (0);
}

int	ft_is_in_dquotes(char *line, int ind)
{
	int	i;
	int	ns;
	int	nd;

	i = 0;
	ns = 0; // 1 = open quote ; 0 = closed quote
	nd = 0; // 1 = open quote ; 0 = closed quote
	while (i <= ind)
	{
		if (line[i] == '\'' && nd == 0)
			ns = !ns;
		else if (line[i] == '\"' && ns == 0)
			nd = !nd;
		i++;
	}
	if (nd != 0)
		return (1);
	return (0);	
}

int	ft_is_in_quotes(char *line, int ind)
{
	if (ft_is_in_dquotes(line, ind) || ft_is_in_squotes(line, ind))
		return (1);
	return (0);
}

t_line_token	ft_find_token_type(char *str, int i)
{
	if (ft_strncmp(&str[i], ">", 1) == 0 && str[i + 1] != '>')
		return (S_GREAT);
	else if (ft_strncmp(&str[i], "<", 1) == 0 && str[i + 1] != '<')
		return (S_LESS);
	else if (ft_strncmp(&str[i], ">>", 2) == 0)
		return (D_GREAT);
	else if (ft_strncmp(&str[i], "<<", 2) == 0)
		return (D_LESS);
	else if (ft_strncmp(&str[i], "|", 1) == 0)
		return (PIPE);
	else if (ft_is_doll(str, i))
		return (DOLL);
	/*else if (ft_strncmp(str, "(", 1) == 0)
		return (O_PAR);
	else if (ft_strncmp(str, ")", 1) == 0)
		return (C_PAR);
	else if (ft_strncmp(str, "||", 2) == 0)
		return (OR);
	else if (ft_strncmp(str, "&&", 2) == 0)
		return (AND);*/
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

int	ft_is_operand(char *str, int i)
{
	if (ft_strncmp(&str[i], ">", 1) == 0)
		return (1);
	else if (ft_strncmp(&str[i], "<", 1) == 0)
		return (1);
	else if (ft_strncmp(&str[i], "|", 1) == 0)
		return (1);
	else
		return (0);
}

void	ft_skip_spaces(char *str, int *i)
{
	while (ft_isspace(str[*i]) == 1)
		(*i)++;
}

int	ft_doll_len(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i + len] && str[i + len] != ' ')
		len ++;
	return (len);
}

char	*ft_extract_title_doll(char *str, int *i)
{
	int		j;
	char	*title;

	j = 0;
	title = (char *)malloc((ft_doll_len(str, *i) + 1) * sizeof(char));
	if (!title)
		return (NULL);
	while (str[*i] && str[*i] != ' ')
	{
		title[j] = str[*i];
		j++;
		(*i)++;
	}
	title[j] = '\0';
	return (title);
}



int	ft_quoted_len(char *str, int i) //rajouter le cas ou le premier caractere est ' ou "
{
	int	len;

	len = 0;
	if (str[i] == '\'')
	{
		while (str[i + len] && str[i + len] != '\'')
			len ++;
	}
	else if (str[i] == '\"')
	{
		while (str[i + len] && str[i + len] != '\"')
			len ++;
	}
	return (len);
}

int	ft_strlen_content(char *str, int i) //rajouter le cas ou le premier caractere est ' ou "
{
	int	len;

	len = 0;
	if (str[i] == '\'' || str[i] == '\"')
		return (ft_quoted_len(str, i));
	while (str[i] && ft_is_operand(str, i) == 0 && ft_is_doll(str, i) == 0)
	{
		i++;
		len ++;
	}
	return (len);
}

char	*ft_extract_content(char *line, int *i)
{
	int		len;
	char	*str;
	int		j;

	len = ft_strlen_content(line, *i);
	str = (char *)malloc((len + 1) * sizeof(char));
	j = 0;
	if (!str)
		return (NULL);
	while (line[*i] && ft_is_operand(line, *i) == 0 && ft_is_doll(line, *i) == 0 && ft_is_in_quotes(line, *i) == 0)
	{
		str[j] = line[*i];
		j++;
		(*i)++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_extract_sq_content(char *line, int *i)
{
	int		len;
	char	*str;
	int		j;

	len = ft_strlen_content(line, *i);
	str = (char *)malloc((len + 1) * sizeof(char));
	j = 0;
	if (!str)
		return (NULL);
	(*i)++;
	while (line[*i] != '\'')
	{
		str[j] = line[*i];
		j++;
		(*i)++;
	}
	(*i)++;
	str[j] = '\0';
	return (str);
}

char	*ft_extract_dq_content(char *line, int *i, t_token_list **list)
{
	int		len;
	char	*str;
	int		j;

	len = ft_strlen_content(line, *i);
	str = (char *)malloc((len + 1) * sizeof(char));
	j = 0;
	if (!str)
		return (NULL);
	(*i)++;
	while (line[*i] != '\"')
	{
		if (ft_is_doll(line, *i) == 1)
		{
			if (!ft_append_content(line, i, list))
				return (NULL);
			break;
		}
		str[j] = line[*i];
		j++;
		(*i)++;
	}
	if (line[j] == '\"')
		(*i)++;
	str[j] = '\0';
	return (str);
}

t_token_list	*ft_append_content(char *line, int *i, t_token_list **list)
{
	t_token_list	*token;

	token = (t_token_list *)ft_calloc(1, sizeof(t_token_list));
	if (!token)
		return (NULL);
	token->type = ft_find_token_type(line, *i);
	if (token->type == DOLL)
		token->val = ft_extract_title_doll(line, i);
	else
		token->val = ft_extract_content(line, i);
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

t_token_list	*ft_append_squoted(char *line, int *i, t_token_list **list)
{
	t_token_list	*token;

	token = (t_token_list *)ft_calloc(1, sizeof(t_token_list));
	if (!token)
		return (NULL);
	token->type = CONTENT;
	token->val = ft_extract_sq_content(line, i);
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

t_token_list	*ft_append_dquoted(char *line, int *i, t_token_list **list)
{
	t_token_list	*token;

	token = (t_token_list *)ft_calloc(1, sizeof(t_token_list));
	if (!token)
		return (NULL);
	token->type = CONTENT;
	token->val = ft_extract_dq_content(line, i, list);
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

int	ft_quote_error(char *line)
{
	int	i;
	int	ns;
	int	nd;

	i = 0;
	ns = 0; // 1 = open quote ; 0 = closed quote
	nd = 0; // 1 = open quote ; 0 = closed quote
	while (line[i])
	{
		if (line[i] == '\'' && nd == 0)
			ns = !ns;
		else if (line[i] == '\"' && ns == 0)
			nd = !nd;
		i++;
	}
	if (nd != 0 || ns != 0)
		return (1);
	return (0);
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
	else if (token->type == PIPE || token->type == S_LESS || token->type == S_GREAT)
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

t_token_list	*ft_deal_content(char *line, int *i, t_token_list **list)
{
	t_token_list	*res;

	res = NULL;
	while (line[*i])
	{
		ft_skip_spaces(line, i);
		if (line[*i] == '\'')
			res = ft_append_squoted(line, i, list);
		else if (line[*i] == '\"')
			res = ft_append_dquoted(line, i, list);
		else
			res = ft_append_content(line, i, list);
		if (res == NULL)
			return (NULL);
	}
	return (*list);
}

t_token_list	**ft_build_token_list(char *line)
{
	t_token_list	**list;
	int				i;
	t_token_list	*err;

	i = 0;
	if (ft_quote_error(line) == 1)
			return (NULL);
	list = (t_token_list **)ft_calloc(1, sizeof(t_token_list *));
	if (!list)
		return (NULL);
	*list = NULL;
	while (line[i])
	{
		ft_skip_spaces(line, &i);
		if (ft_is_operand(line, i) == 1)
			err = ft_append_operand(line, &i, list);
		else
			err = ft_deal_content(line, &i, list);
		if(!err)
			return(ft_free_list(list), NULL);
	}
	return (list);
}
