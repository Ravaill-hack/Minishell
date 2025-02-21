/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:00:41 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/21 13:50:59 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/*
int	ft_is_var_env(char **env, char *str)
{
	
}

int	ft_strlen_var_env(char **env, char *str)
{
	int		len;
	int		i;
	int		j;

	len = 0;
	i = ft_get_line_env(env, str); //ne pas utiliser str ici mais plutot find_env_key(str)
	j = ft_strchr(str[i], '=') + 1 - str; //on trouve l'indice j de depart de la valeur de la variable
	while (str[j])
	{
		len++;
		j++;
	}
	return (len);
}

int	ft_insert_var_env(char **env, char *p_nl, int *j, char *p_ol)
{
	int	len_i;
	int	len_j;

	len_i = 0;
	len_j = 0;
	return (len_i);
}

int	ft_insert_exit_stat(t_var var, char *p_nl, int *j, char *p_ol)
{
	return (1);
}

char	*ft_handle_doll(char *str, t_var var, char **env)
{
	char	*line;
	int		i;
	int		j;
	int		len;

	len = ft_str_doll_len(env, str[i]);
	line = (char *)malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && ft_is_var_env(env, &(str[i])))
			i += ft_insert_var_env(env, &(line[j]), &j, &(str[i]));
		else if (str[i] == '$' && str[i + 1] == '?')
			i += ft_insert_exit_stat(var, &(line[j]), &j, &(str[i]));
		else if (str[i] == '$' && str[i + 1])
			break ; //si ce n'est ni une variable d'env ni un ?, alors on ne copie rien de plus (ni meme le $)
		line[j] = str[i];
		j++;
		i++;
	}
	return (line);
}

char	**ft_expand_content(char *str, t_var var)
{
	char	**split;
	int		i;
	char	*p;

	i = 0;
	p = 0;
	split = ft_special_split(str, ' '); //A FAIRE : un split qui ne divise pas quand on est dans des quotes
	if (!split)
		return (NULL);
	while (split[i]) //si on ne detecte aucun $ ou qu'on detecte des dollars seuls on ne fait rien et on retourne split
	{
		p = ft_strchr(split[i], '$');
		if (p != NULL && (p + 1) != '\0')
			split[i] = ft_handle_doll(split[i], var, var.env);
		i++;
	}
	return (split);
}

int	ft_develop_strings(t_var var, t_token_list **list)
{
	t_token_list	*token;

	token = *list;
	while (token)
	{
		if (token->type == CONTENT)
			token->split_val = ft_expand_content(token->val, var);
		else
		{
			token->split_val = NULL;
			*(token->split_val) = NULL;
		}
		token = token->next;
	}
}
*/

int	ft_parse_line(t_var *var)
{
	//var->split_line = ft_split(var->line, ' ');
	var->token_list = ft_build_token_list(var->line);
	if (!var->token_list)
		return (FAILURE);
	//	return (ft_free_line(*var), FAILURE);
	//ft_develop_strings(*var, var->token_list);
	return (SUCCESS);
}