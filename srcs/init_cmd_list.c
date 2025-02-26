/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:31:57 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/26 08:53:41 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_doll_var_exists(char *str, char **env)
{
	int	i;

	i = 0;
	//if (str[0] == '?')
	//	return (1);
	while (env[i])
	{
		if (ft_strncmp(str, env[i], ft_strlen(str)) == 0
			&& env[i][ft_strlen(str)] == '=')
			return (1);
		i++;
	}
	return (0);
}

t_token_list	*ft_go_to_next_node(t_token_list *node)
{
	node = node->next;
	while (node)
	{
		if (node->prev->print_space_after == 1 
			&& (node->type == CONTENT || node->type == DOLL))
			break;
		node = node->next;
	}
	return (node);
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

char	*ft_dolljoin(char *str, char *doll, char **env)
{
	size_t	src_len;
	size_t	size;
	char	*val_doll;
	char	*joined_str;

	src_len = ft_strlen(str);
	size = ft_strlen(str) + (size_t)ft_doll_val_len(doll, env);
	if (size == 0)
		return (NULL);
	joined_str = (char *)ft_calloc((size + 1), sizeof(char));
	if (!joined_str)
		return (NULL);
	val_doll = ft_extract_env_value_from_key(env, &(doll[1]));
	if (str)
		ft_strlcpy(joined_str, str, src_len + 1);
	if (val_doll)
		ft_strlcat(joined_str, val_doll, size + 1);
	if (!str && !val_doll)
		return (NULL);
	return (joined_str);
}

int	ft_find_special_len(t_token_list *node, char **env)
{
	int	len;
	int	len_doll;

	len = 0;
	len_doll = 0;
	while (node && (node->print_space_after == 0 || (node->type != CONTENT
		|| node->type != DOLL)))
	{
		if (node->type == DOLL)
		{
			len_doll = ft_doll_val_len(node->val, env);
			if (len_doll == 0)
				node = node->next;
			else
				len += len_doll;
		}
		else if (node->type == CONTENT)
			len += ft_strlen((const char *)node->val);
		node = node->next;
	}
	return (len);
}

t_token_list	*ft_go_to_cmd_node(t_token_list	*list, int i)
{
	int	ind;

	ind = 0;
	while (list && ind < i)
	{
		if (list->type == PIPE)
			ind++;
		list = list->next;
	}
	return (list);
}

/*
char	*ft_create_first_line(t_token_list *node, char **env)
{
	char	*str;
	//char	*tmp;
	//int		len;

	//len = ft_find_special_len(node, env);
	str = NULL;
	//tmp = NULL;
	while (node && (node->type == CONTENT || node->type == DOLL))
	{
		//tmp = str;	
		if (node->type == CONTENT)
			str = ft_strjoin(str, node->val);
		else if (node->type == DOLL && ft_doll_var_exists(&(node->val[1]), env))
			str = ft_dolljoin(str, node->val, env);
		//free (tmp);
		if (!str)
			return (NULL);
		if (node->print_space_after != 0)
			break;
		node = node->next;
	}
	//str[len] = '\0';
	return (str);
}
*/

char	*ft_fill_arg(t_token_list *node, t_var *var)
{
	char	*str;
	//char	*tmp;
	//int		len;

	//len = ft_find_special_len(node, env);
	str = NULL;
	//tmp = NULL;
	while (node && (node->type == CONTENT || node->type == DOLL))
	{
		//tmp = str;	
		if (node->type == CONTENT)
			str = ft_strjoin(str, node->val);
		else if (node->type == DOLL && ft_doll_var_exists(&(node->val[1]), var->env))
			str = ft_dolljoin(str, node->val, var->env);
		//free (tmp);
		if (!str)
			return (NULL);
		if (node->print_space_after != 0)
			break;
		node = node->next;
	}
	//str[len] = '\0';
	return (str);
}

char	**ft_token_list_to_char_array(t_token_list *node, t_var *var)
{
	char	**array;
	int		len;
	int		j;

	len = ft_nb_str(node, var->env);
	j = 0;
	array = (char **)malloc((len + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	/*array[0] = ft_create_first_line(node, env);
	if (!array[0])
		return (NULL);*/
	while (j < len)
	{
		array[j] = ft_fill_arg(node, var);
		//if (!array[j])
		//	return (ft_free_char_array(array, j), NULL);
		node = ft_go_to_next_node(node);
		if (array[j])
			j++;
	}
	array[j] = NULL;
	return (array);
}

t_cmd	*ft_create_cmd_node(t_var *var, int i)
{
	t_token_list	*token_node;
	t_cmd			*cmd_node;

	cmd_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd_node)
		return (NULL);
	token_node = ft_go_to_cmd_node(*(var->token_list), i);
	cmd_node->arg = ft_token_list_to_char_array(token_node, var);
	if (!cmd_node->arg)
		return (NULL);
//	cmd_node->name = ft_extract_cmd_name(cmd_node->arg[0]); //A FAIRE fonction pour isoler le nom de la commande
//	cmd_node->path = ft_extract_cmd_path(cmd_node->arg[0]); //A FAIRE fonction pour isoler le chemin de la commande
//	cmd_node->opt = ft_extract_cmd_opt(cmd_node->arg); //A FAIRE fonction pour isoler les options de la commande
	//cmd_node->fd_in = ft_find_fdin(token_node, var->env); //A FAIRE fonction pour renvoyer le fd de lecture : peut etre un
	// heredoc ou rien ou un fichier ou un canal d'un int[2] qui stockera en ecriture le resultat d'un autre pipe
	//cmd_node->fd_out = ft_find_fdout(token_node, var->env); //A FAIRE fonction pour renvoyer le fd d'ecriture' : peut etre un
	// append ou STDOUT ou un fichier ou un canal d'un int[2] qui utilisera en lecture le resultat d'un autre pipe
	return (cmd_node);
}

t_cmd	**ft_build_cmd_list(t_var *var)
{
	t_cmd	**cmd_list;
	int		i;

	i = 0;
	var->nb_cmd = ft_nb_pipes(*(var->token_list)) + 1;
	cmd_list = (t_cmd **)malloc((var->nb_cmd + 1) * sizeof(t_cmd *));
	if(!cmd_list)
		return (NULL);
	while (i < var->nb_cmd)
	{
		cmd_list[i] = ft_create_cmd_node(var, i);
		if (!cmd_list[i])
			return (ft_free_cmd_list(var, cmd_list, i), NULL);
		i++;
	}
	cmd_list[i] = NULL;
	return (cmd_list);
}
