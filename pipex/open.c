/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:37:07 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/05 14:38:04 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_open_fd_in(char *file)
{
	int	fd_in;

	fd_in = open(file, O_RDONLY);
	if (fd_in == -1)
		ft_error ("Error : cannot open infile\n");
	return (fd_in);
}

int	ft_open_fd_out(char *file, int i)
{
	int	fd_out;

	if (i == 0)
		fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out == -1)
		ft_error("Error : cannot create or write in outfile\n");
	return (fd_out);
}

int	ft_find_fd_in(char **argv)
{
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		return (ft_open_fd_in(argv[2]));
	else
		return (ft_open_fd_in(argv[1]));
}
