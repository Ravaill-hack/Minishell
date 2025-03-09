/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:50:06 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/09 19:12:55 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_infile(char *str, t_cmd *node)
{
	if (node->fd_in.is_def)
	{
		if (node->fd_in.fd != 0 && node->fd_in.fd != -1)
			close(node->fd_in.fd);
		if (node->heredoc)
			free(node->heredoc);
	}
	node->heredoc = NULL;
	node->fd_in.fd = open(str + 1, O_RDONLY);
	if (node->fd_in.fd == -1)
		return (FAILURE);
	node->fd_in.type = SIMPLE;
	node->fd_in.is_def = 1;
	return (SUCCESS);
}

int	ft_set_outfile_append(char *str, t_cmd *node)
{
	if (node->fd_out.is_def)
	{
		if (node->fd_out.fd != 1 && node->fd_out.fd != -1)
			close(node->fd_out.fd);
	}
	node->fd_out.fd = open(str + 2, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (node->fd_out.fd == -1)
		return (FAILURE);
	node->fd_out.type = DOUBLE;
	node->fd_out.is_def = 1;
	return (SUCCESS);
}

int	ft_set_outfile_trunc(char *str, t_cmd *node)
{
	if (node->fd_out.is_def)
	{
		if (node->fd_out.fd != 1 && node->fd_out.fd != -1)
			close(node->fd_out.fd);
	}
	node->fd_out.fd = open(str + 1, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (node->fd_out.fd == -1)
		return (FAILURE);
	node->fd_out.is_def = 1;
	node->fd_out.type = SIMPLE;
	return (SUCCESS);
}

int check_signal(void)
{
    if (g_while_hd == 0)
        return 1; // Force readline à retourner
    return 0;
}

int	ft_while_heredoc(char *line, char *heredoc, t_shell *shell)
{
	int		fd_pipe[2];
	int		i;

	(void)shell;
	i = 0;
	if (pipe(fd_pipe) == -1)
		return (-1);
	g_while_hd = 1;
	rl_event_hook = check_signal;
	while (g_while_hd == 1)
	{
		i++;
		line = readline("> ");
		if (!line || g_while_hd == 0)
		{
			ft_putstr_fd("warning: here-document at line ", 2);
			ft_putnbr_fd(i, 2);
			ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(heredoc, 2);
			ft_putstr_fd("')\n", 2);
			break ;
		}
		if (ft_strncmp(line, heredoc, ft_strlen(line)) == 0 || g_while_hd == 0)
		{
			free (line);
			break ;
		}
		write(fd_pipe[1], line, strlen(line));
		write(fd_pipe[1], "\n", 1);
		free(line);
	}
	close(fd_pipe[1]);
	g_while_hd = 0;
	rl_event_hook = NULL;
	return (fd_pipe[0]);
}

int	ft_set_heredoc(char *str, t_cmd *node, t_shell *shell)
{
	char	*line;

	line = NULL;
	if (node->fd_in.is_def)
	{
		if (node->fd_in.fd != 0 && node->fd_in.fd != -1)
			close(node->fd_in.fd);
		if (node->heredoc)
			free(node->heredoc);
	}
	node->heredoc = ft_strdup(str + 2);
	if (!(node->heredoc))
		return (FAILURE);
	node->fd_in.fd = ft_while_heredoc(line, node->heredoc, shell);
	if (node->fd_in.fd == -1)
		return (FAILURE);
	node->fd_in.is_def = 1;
	node->fd_in.type = DOUBLE;
	node->need_pipe_in = 1;
	return (SUCCESS);
}
