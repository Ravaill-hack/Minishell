/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:35:55 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/11 09:53:15 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_redir_in(int *is_redir, char **raw, int i)
{
	if (is_redir[i] == 1 && raw[i][0] == '<' && raw[i][1] != '<')
		return (1);
	return (0);
}

int	ft_is_redir_hdc(int *is_redir, char **raw, int i)
{
	if (is_redir[i] == 1 && raw[i][0] == '<' && raw[i][1] == '<')
		return (1);
	return (0);
}

int	ft_is_redir_out_trunc(int *is_redir, char **raw, int i)
{
	if (is_redir[i] == 1 && raw[i][0] == '>' && raw[i][1] != '>')
		return (1);
	return (0);
}

int	ft_is_redir_out_append(int *is_redir, char **raw, int i)
{
	if (is_redir[i] == 1 && raw[i][0] == '>' && raw[i][1] == '>')
		return (1);
	return (0);
}

int	ft_redir_failure(t_cmd *node, int i)
{
	ft_open_error(node->raw[i] + 1);
	ft_close_fds(node);
	return (FAILURE);
}
