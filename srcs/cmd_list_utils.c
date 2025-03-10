/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:56:02 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/10 19:28:40 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE //

#include "minishell.h"

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

char	*ft_dup_operand(t_line_token type)
{
	if (type == S_LESS)
		return (ft_strdup ("<"));
	else if (type == D_LESS)
		return (ft_strdup ("<<"));
	else if (type == S_GREAT)
		return (ft_strdup (">"));
	else if (type == D_GREAT)
		return (ft_strdup (">>"));
	return (NULL);
}

char	*ft_nb_ex_join(char *str, char *doll, int nb_ex)
{
	size_t	size_tot;
	char	*val_doll;
	char	*joined_str;

	size_tot = ft_strlen(str) + ft_strlen_nb(nb_ex);
	if (doll[2] != '\0')
		size_tot += ft_strlen(&doll[2]);
	joined_str = (char *)ft_calloc((size_tot + 1), sizeof(char));
	if (!joined_str)
		return (NULL);
	val_doll = ft_itoa(nb_ex);
	ft_strlcpy(joined_str, str, ft_strlen(str) + 1);
	ft_strlcat(joined_str, val_doll, ft_strlen(str) + ft_strlen_nb(nb_ex) + 1);
	if (doll[2] != '\0')
		ft_strlcat(joined_str, &(doll[2]), size_tot + 1);
	return (joined_str);
}

int	ft_is_nb_exit(char *str)
{
	if (str[0] == '?')
		return (1);
	return (0);
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
