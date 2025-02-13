/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:20:34 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/05 14:40:09 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>

int		ft_open_fd_in(char *file);
int		ft_open_fd_out(char *file, int i);
int		ft_find_fd_in(char **argv);
int		exec_cmds(char *cmd, char **env);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
void	ft_free(char **str);
int		find_line(char *title, char **env);
char	*extract_env(char *title, char **env);
char	*extract_path(char *cmd, char **env);
int		ft_error(char *str);
void	close_2_fd(int fd_in, int fd_out);

#endif