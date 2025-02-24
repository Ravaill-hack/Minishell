/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:31:57 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/24 17:56:53 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_doll_val_len(char *doll, char **env)
{
	int		len;
	char	*ptr;

	len = 0;
	ptr = ft_extract_env_value_from_key(env, &(doll[1]));
	while (ptr[len])
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
	joined_str = (char *)ft_calloc((size + 1), sizeof(char));
	if (!joined_str)
		return (NULL);
	val_doll = ft_extract_env_value_from_key(env, &(doll[1]));
	ft_strlcpy(joined_str, str, src_len + 1);
	ft_strlcat(joined_str, val_doll, size + 1);
	return (joined_str);
}

int	ft_find_special_len(t_token_list *node, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (node && (node->print_space_after == 0 || node->type != CONTENT
		|| node->type != DOLL))
	{
		if (node->type == DOLL)
			len += ft_doll_val_len(node->val, env);
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

char	*ft_fill_arg(t_token_list *node, char **env)
{
	char	*str;
	char	*tmp;
	int		len;

	len = ft_find_special_len(node, env);
	str = NULL;
	tmp = NULL;
	while (node && (node->type == CONTENT || node->type == DOLL))
	{
		tmp = str;
		if (node->type == CONTENT)
			str = ft_strjoin(str, node->val);
		else if (node->type == DOLL)
			str = ft_dolljoin(str, node->val, env);
		free (tmp);
		if (!str)
			return (NULL);
		if (node->print_space_after != 0)
			break;
		node = node->next;
	}
	str[len] = '\0';
	return (str);
}

char	**ft_token_list_to_char_array(t_token_list *node, char **env)
{
	char	**array;
	int		len;
	int		j;

	len = ft_nb_str(node);
	j = 0;
	array = (char **)malloc((len + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (j < len)
	{
		array[j] = ft_fill_arg(node, env);
		if (!array[j])
			return (ft_free_arg_array(array, j), NULL); //A FAIRE fonction pour free un tableau de chaines jusqu'a la ieme chaine
		node = ft_go_to_next_node(node); //A FAIRE fonction pour aller au noeud apres le premier prochain noeud suivi par un espace. renvoie NULL si c'est la fin 
		//i.e le prochain noeud n'existe pas ou est autre chose qu'un DOLL ou un CONTENT
		j++;
	}
	array[j] = NULL;
	return (array);
}

t_cmd	*ft_create_cmd_node(t_var *var, int i)
{
	t_token_list	*token_node;
	t_cmd			*cmd_node;
	char			**tab_args;

	cmd_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd_node)
		return (NULL);
	token_node = ft_go_to_cmd_node(var->token_list, i);
	cmd_node->arg = ft_token_list_to_char_array(token_node, var->env);
	if (!cmd_node->arg)
		return (NULL);
	cmd_node->name = ft_extract_cmd_name(cmd_node->arg[0]); //A FAIRE fonction pour isoler le nom de la commande
	cmd_node->path = ft_extract_cmd_path(cmd_node->arg[0]); //A FAIRE fonction pour isoler le chemin de la commande
	cmd_node->opt = ft_extract_cmd_opt(cmd_node->arg); //A FAIRE fonction pour isoler les options de la commande
	cmd_node->fd_in = ft_find_fdin(token_node, var->env); //A FAIRE fonction pour renvoyer le fd de lecture : peut etre un
	// heredoc ou rien ou un fichier ou un canal d'un int[2] qui stockera en ecriture le resultat d'un autre pipe
	cmd_node->fd_out = ft_find_fdout(token_node, var->env); //A FAIRE fonction pour renvoyer le fd d'ecriture' : peut etre un
	// append ou STDOUT ou un fichier ou un canal d'un int[2] qui utilisera en lecture le resultat d'un autre pipe
}

t_cmd	**ft_build_cmd_list(t_var *var)
{
	t_cmd	**cmd_list;
	int		len;
	int		i;

	i = 0;
	len = ft_nb_pipes(var->token_list) + 1;
	cmd_list = (t_cmd **)malloc((len + 1) * sizeof(t_cmd *));
	if(!cmd_list)
		return (NULL);
	while (i < len)
	{
		cmd_list[i] = ft_create_cmd_node(var, i);
		if (!cmd_list[i])
			return (ft_free_cmd_list(cmd_list, i), NULL); //A FAIRE fonction pour free un tableau de structures jusqu'a la ieme structure
		i++;
	}
	cmd_list[i] = NULL;
	return (cmd_list);
}
