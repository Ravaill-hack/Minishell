/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_build.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:48:38 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/14 15:45:27 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_fd(t_cmd *node)
{
	node->fd_in.is_def = 0;
	node->fd_in.fd = 0;
	node->fd_in.type = NONE;
	node->fd_out.fd = 1;
	node->fd_out.is_def = 0;
	node->fd_out.type = NONE;
}

int	ft_close_fds(t_cmd *node)
{
	if (node->fd_in.fd != -1 && node->fd_in.fd != 0)
		close(node->fd_in.fd);
	if (node->fd_out.fd != -1 && node->fd_out.fd != 1)
		close(node->fd_out.fd);
	if (node->heredoc)
		free(node->heredoc);
	return (FAILURE);
}

int	ft_fill_fd(t_cmd *node, t_var *var)
{
	int	i;
	int	res;

	i = 0;
	res = SUCCESS;
	while (node->raw[i])
	{
		if (node->is_redir[i] == 1 && ft_token_redir_error(node, i) == 1)
			return (FAILURE);
		else if (ft_is_redir_hdc(node->is_redir, node->raw, i) == 1)
			res = ft_set_heredoc(node->raw[i], node, var);
		else if (ft_is_redir_in(node->is_redir, node->raw, i) == 1)
			res = ft_set_infile(node->raw[i], node);
		else if (ft_is_redir_out_append(node->is_redir, node->raw, i) == 1)
			res = ft_set_outfile_append(node->raw[i], node);
		else if (ft_is_redir_out_trunc(node->is_redir, node->raw, i) == 1)
			res = ft_set_outfile_trunc(node->raw[i], node);
		if (res == FAILURE)
			return (ft_redir_failure(node, i));
		i++;
	}
	return (SUCCESS);
}

int	**ft_init_pipes(int nb_pipes)
{
	int	i;
	int	**pipes;

	i = 0;
	pipes = (int **)malloc((nb_pipes + 1) * sizeof(int *));
	if (!pipes)
		return (NULL);
	while (i < nb_pipes)
	{
		pipes[i] = (int *)malloc(2 * sizeof(int));
		if (!pipes[i])
			return (NULL);
		i++;
	}
	pipes[i] = NULL;
	return (pipes);
}

int	ft_set_pipes(t_cmd **cmd, int nb_cmd, int **pipes)
{
	int	i;

	i = 0;
	ft_set_pipes_needs(cmd, nb_cmd);
	while (i < nb_cmd - 1)
	{
		if (cmd[i]->need_pipe_out == 1 || cmd[i + 1]->need_pipe_in == 1)
		{
			if (pipe(pipes[i]) == -1)
				return (FAILURE);
			if (cmd[i]->need_pipe_out == 1)
				cmd[i]->fd_out.fd = pipes[i][1];
			if (cmd[i + 1]->need_pipe_in == 1)
				cmd[i + 1]->fd_in.fd = pipes[i][0];
			if (cmd[i]->need_pipe_out == 0)
				close(pipes[i][1]);
			if (cmd[i + 1]->need_pipe_in == 0)
				close(pipes[i][0]);
		}
		i++ ;
	}
	return (SUCCESS);
}
