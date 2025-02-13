/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:56:40 by juduchar          #+#    #+#             */
/*   Updated: 2025/01/22 11:27:29 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_file	*ft_get_or_create_file_struct(int fd, t_file **files)
{
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (!files[fd])
	{
		files[fd] = (t_file *) malloc(sizeof(t_file));
		if (!files[fd])
			return (NULL);
		files[fd]->fd = fd;
		files[fd]->remaining = NULL;
		files[fd]->buffer[0] = '\0';
	}
	return (files[fd]);
}

static void	ft_free_file(t_file **file)
{
	if (!file || !*file)
		return ;
	if ((*file)->remaining)
	{
		free((*file)->remaining);
		(*file)->remaining = NULL;
	}
	free(*file);
	*file = NULL;
}

static char	*ft_extract_line(char **remaining)
{
	char	*nl_pos;
	char	*temp;
	char	*line;

	if (!*remaining || !**remaining)
		return (NULL);
	nl_pos = ft_strchr(*remaining, '\n');
	if (!nl_pos)
		return (NULL);
	line = ft_strndup(*remaining, nl_pos - *remaining + 1);
	if (!line)
		return (NULL);
	temp = ft_strndup(nl_pos + 1, ft_strlen(nl_pos + 1));
	if (!temp)
	{
		free(line);
		return (NULL);
	}
	free(*remaining);
	*remaining = temp;
	return (line);
}

static char	*ft_finalize_line(t_file **file_ptr, ssize_t bytes_read)
{
	t_file	*file;
	char	*line;

	file = *file_ptr;
	if (bytes_read < 0 || !file->remaining || !*file->remaining)
	{
		ft_free_file(file_ptr);
		return (NULL);
	}
	line = ft_strndup(file->remaining, ft_strlen(file->remaining));
	ft_free_file(file_ptr);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_file	*files[OPEN_MAX];
	t_file			*file;
	ssize_t			bytes_read;
	char			*line;

	file = ft_get_or_create_file_struct(fd, files);
	if (!file)
		return (NULL);
	line = ft_extract_line(&file->remaining);
	if (line)
		return (line);
	bytes_read = read(fd, file->buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		file->buffer[bytes_read] = '\0';
		file->remaining = ft_strnjoin(file->remaining, file->buffer,
				ft_strlen(file->remaining), bytes_read);
		if (!file->remaining)
			return (NULL);
		line = ft_extract_line(&file->remaining);
		if (line)
			return (line);
		bytes_read = read(fd, file->buffer, BUFFER_SIZE);
	}
	return (ft_finalize_line(&files[fd], bytes_read));
}
