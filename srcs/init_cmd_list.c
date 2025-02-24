/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:31:57 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/24 17:02:02 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_fill_arg(t_token_list *node, int j, char **env)
{
	char	*str;
	char	*tmp;
	int		len;

	len = ft_find_special_len(node, j); //A FAIRE fonction pour fcalculer la taille d'une chaine de caracteres qui pourra etre composee
	// de variables $, de series de "" non separes par des espaces, etc
	str = NULL;
	tmp = NULL;
	while (node && (node->type == CONTENT || node->type == DOLL))
	{
		tmp = str;
		if (node->type == CONTENT)
			str = ft_strjoin(str, node->val);
		else if (node->type == DOLL)
			str = ft_dolljoin(str, node->val, env); //A FAIRE fonction sur le modele de ft_strjoin mais qui puisse concatener une chaine de caracteres
			//avec une variable $
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
		array[j] = ft_fill_arg(node, j, env);
		if (!array[j])
			return (ft_free_arg_array(array, j), NULL); //A FAIRE fonction pour free un tableau de chaines jusqu'a la ieme chaine
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
	token_node = ft_go_to_cmd_node(var->token_list, i); //A FAIRE fonction pour renvoyer l'adresse du premier token du i-ieme "noeud" de commande
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
