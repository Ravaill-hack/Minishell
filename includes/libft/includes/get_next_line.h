/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:10:48 by juduchar          #+#    #+#             */
/*   Updated: 2025/01/22 11:27:57 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# if BUFFER_SIZE > 1000000
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>

typedef struct s_file
{
	int		fd;
	char	*remaining;
	char	buffer[BUFFER_SIZE + 1];
}				t_file;

char	*get_next_line(int fd);

#endif
