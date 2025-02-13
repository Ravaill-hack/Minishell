/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 10:22:19 by juduchar          #+#    #+#             */
/*   Updated: 2025/01/11 08:48:41 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Paramètres :
// lst : L’adresse du pointeur vers le premier élément de la liste.
// new : L’adresse de l’élément à rajouter à la liste.

// Valeur de retour :
// Aucune

// Description :
// Ajoute l’élément ’new’ au début de la liste.
void	ft_lstadd_front(t_list **lst, t_list *new_lst)
{
	if (!lst || !new_lst)
		return ;
	if (!*lst)
	{
		*lst = new_lst;
		new_lst->next = NULL;
		return ;
	}
	new_lst->next = *lst;
	*lst = new_lst;
}
