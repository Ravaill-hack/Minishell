/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handle_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:14:52 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/11 11:03:31 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_read_while_heredoc(char *line, int i, char *heredoc, int pipe1)
{
	while (g_while_hd == 1)
	{
		i++;
		line = readline("> ");
		if (!line || g_while_hd == 0)
		{
			ft_print_error_hdc(i, heredoc);
			break ;
		}
		if (ft_strncmp(line, heredoc, ft_strlen(line)) == 0 || g_while_hd == 0)
		{
			free (line);
			break ;
		}
		write(pipe1, line, strlen(line));
		write(pipe1, "\n", 1);
		free(line);
	}
	return (0);
}
