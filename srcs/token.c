/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:55:13 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/19 16:58:26 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_line_token	ft_find_token_type(char *str)
{
	if (ft_strncmp(str, ">", 1) == 0 && *(str + 1) != '>')
		return (S_GREAT);
	else if (ft_strncmp(str, "<", 1) == 0 && *(str + 1) != '<')
		return (S_LESS);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (D_GREAT);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (D_LESS);
	else if (ft_strncmp(str, "|", 1) == 0)
		return (PIPE);
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

/*
t_token_list	*ft_append_token(char *word, t_token_list **list)
{
	t_token_list	*token;

	token = (t_token_list *)ft_calloc(1, sizeof(t_token_list));
	if (!token)
		return (NULL);
	token->type = ft_find_token_type(word);
	// TODO
	token->content = ft_find_token_content(word);
	if (token->content)
	{
		if (token->token == CONTENT && token->content == STR)
			token->val = ft_strdup(word);
		else if (token->content == CHAR)
			token->val = *word;
		else if (token->content == INT)
			token->val = ft_atoi(word);
		else if (token->content == DOL)
			...
	}
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
*/

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
/*
t_token_list	**ft_build_token_list(char **split_line)
{
	t_token_list	**list;
	int				i;

	i = 0;
	list = (t_token_list **)ft_calloc(1, sizeof(t_token_list *));
	if (!list)
		return (NULL);
	*list = NULL;
	while (split_line[i])
	{
		if (!ft_append_token(split_line[i], list))
			return (ft_free_token_list_until(list, i), NULL);
		i++;
	}
	return (list);
}


int	ft_nb_char_lft(char *str, int i, char c)
{
	int	nb;

	nb = 0;
	while (i >= 0)
	{
		if (str[i] == c)
			nb++;
		i--;
	}
	return (nb);
}

t_token_list	*ft_append_squoted_str(char *str, int *i, t_token_list **list)
{
	t_token_list	*token;

	token = (t_token_list *)ft_calloc(1, sizeof(t_token_list));
	if (!token)
		return (NULL);
	token->type = CONTENT;
	// TODO
	token->content = ft_find_token_content(word);
	if (token->content)
	{
		if (token->token == CONTENT && token->content == STR)
			token->val = ft_strdup(word);
		else if (token->content == CHAR)
			token->val = *word;
		else if (token->content == INT)
			token->val = ft_atoi(word);
		else if (token->content == DOL)
			...
	}
	token->val = ft_extract_squoted_str(str, i);
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

int	ft_var_env_exists(char *str, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (env[i + len] && env[i + len] != ' ')
		len++;
	while (env[i] && env[i] != ' ')
	{
		if (ft_strncmp(str, env[i], len) == 0 && env[i][len] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen_var_env(char *str, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (env[i + len] && env[i + len] != ' ')
		len++;
	while (!(ft_strncmp(str, env[i], len) == 0 && env[i][len] == '='))
		i++;
	return (ft_strlen(env[i]) - len - 1);
}

char	*ft_extract_squoted_str(char *line, int *i)
{
	int		len;
	int		j;
	char	*str;

	len = 0;
	j = 0;
	str = NULL;
	*i++;
	while (line[len + *i] && line[len + *i] != '\'')
		len++;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (j < len)
	{
		str[j] = line[*i];
		j++;
		(*i)++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_extract_dquoted_str(char *line, int *i, char **env)
{
	int		len;
	int		lendoll;
	int		skip;
	int		j;
	char	*str;

	len = 0;
	lendoll = 0;
	j = 0;
	str = NULL;
	*i++;
	while (line[len + skip + *i] && line[len + skip + *i] != '\"')
	{
		if (line[len + skip + *i] == '$')
		{
			if (ft_var_env_exists(&(line[*i]), env) || line[*i + 1] == '?' && (line[*i + 2] == ' ' || line[*i + 2] == '\0'))
				lendoll += ft_strlen_var_env(&(line[*i]), env);
			skip += ft_strlen_title_var_env(&(line[*i]));
		}
		len++;
	}
	len += lendoll;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (j < len)
	{
		str[j] = line[*i];
		j++;
		(*i)++;
	}
	str[j] = '\0';
	return (str);
}
*/

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

t_token_list	*ft_append_operand(char *line, int *i, t_token_list **list)
{
	t_token_list	*token;

	token = (t_token_list *)ft_calloc(1, sizeof(t_token_list));
	if (!token)
		return (NULL);
	token->type = ft_find_token_type(&(line[*i]));
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

int	ft_strlen_content(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i] && ft_is_operand(str, i) == 0)
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
	while (line[*i] && ft_is_operand(line, *i) == 0)
	{
		str[j] = line[*i];
		j++;
		(*i)++;
	}
	str[j] = '\0';
	return (str);
}

t_token_list	*ft_append_content(char *line, int *i, t_token_list **list)
{
	t_token_list	*token;

	token = (t_token_list *)ft_calloc(1, sizeof(t_token_list));
	if (!token)
		return (NULL);
	token->type = CONTENT;
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

t_token_list	**ft_parse_token_list(char *line, char **env)
{
	t_token_list	**list;
	int				i;

	i = 0;
	(void)env;
	/*if (ft_quote_error(line) == 1)
			return (-1); //envoyer message d'erreur "open quotes detected"
	*/
	list = (t_token_list **)ft_calloc(1, sizeof(t_token_list *));
	if (!list)
		return (NULL);
	*list = NULL;
	while (line[i])
	{
		/*
		if (ft_nb_char_lft(line, i, '\'') % 2 == 1)//dans ce cas la on est a l'interieur d'une quote donc tout ce qui suit jusqu'a la prochaine quote doit etre interprete comme une seule chaine de caracteres
			if (!ft_append_squoted_str(line, &i, list))//en donnant l'adresse de i je peux l'incrementer directement dans la fonction
				return (ft_free_token_list_until(list, i), NULL); 
		else if (ft_nb_char_lft(line, i, '\"') % 2 == 1)//dans ce cas la on est a l'interieur d'une quote donc tout ce qui suit jusqu'a la prochaine quote doit etre interprete comme une seule chaine de caracteres
			if (!ft_append_dquoted_str(line, &i, list))//en donnant l'adresse de i je peux l'incrementer directement dans la fonction
				return (ft_free_token_list_until(list, i), NULL); 	
		else
		{ */
			ft_skip_spaces(line, &i);
			if (ft_is_operand(line, i) == 1)
			{
				if (!ft_append_operand(line, &i, list))
					return (ft_free_list(list), NULL);
			}
			else
			{
				if (!ft_append_content(line, &i, list))
					return (ft_free_list(list), NULL);
			}
		/*
		}
		*/
	}
	return (list);
}
