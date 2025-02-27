/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_build.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:48:38 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/27 16:52:19 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_fd(t_cmd *node)
{
	node->fd_in.is_def = 0;
	node->fd_in.fd = 0;
	node->fd_in.type = SIMPLE;
	node->fd_out.fd = 1;
	node->fd_out.is_def = 0;
	node->fd_out.type = SIMPLE;
}

int	ft_close_fds(t_cmd *node)
{
	close(node->fd_in.fd);
	close(node->fd_out.fd);
	if (node->heredoc)
		free(node->heredoc);
	return (SUCCESS);
}

int	ft_fill_fd(t_cmd *node)
{
	int	i;
	int	res;

	i = 0;
	res = SUCCESS;
	while (node->raw[i])
	{
		if ((node->raw[i][0] == '<' || node->raw[i][0] == '>') && !(node->raw[i][1]))
			return (FAILURE);
		if (node->raw[i][0] == '<' && node->raw[i][1] == '<')
			res = ft_set_heredoc(node->raw[i], node);
		else if (node->raw[i][0] == '<' && node->raw[i][1] != '<')
			res = ft_set_infile(node->raw[i], node);
		else if (node->raw[i][0] == '>' && node->raw[i][1] == '>')
			res = ft_set_outfile_append(node->raw[i], node);
		else if (node->raw[i][0] == '>' && node->raw[i][1] != '>')
			res = ft_set_outfile_trunc(node->raw[i], node);
		if (res == FAILURE)
			return (ft_close_fds(node), FAILURE);
		i++;
	}
	return (SUCCESS);
}
