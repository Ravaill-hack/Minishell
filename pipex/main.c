/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:22:09 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/19 08:38:03 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(char *cmd, char **env)
{
	char	**split_cmd;
	char	*path;
	int		err;

	split_cmd = ft_split(cmd, ' ');
	path = extract_path(split_cmd[0], env);
	err = execve(path, split_cmd, env);
	if (err == -1)
	{
		perror("Error : processus cannot be executed ");
		ft_free(split_cmd);
		free(path);
		exit(EXIT_FAILURE);
	}
}

int	exec_cmds(char *cmd, char **env)
{
	int		fd_pipe[2];
	pid_t	id_cmd;

	if (pipe(fd_pipe) == -1)
		return (ft_error("Error : pipe creation failed\n"));
	id_cmd = fork();
	if (id_cmd == -1)
		return (ft_error("Error : fork execution failed\n"));
	if (id_cmd == 0)
	{
		close(fd_pipe[0]);
		dup2(fd_pipe[1], 1);
		exec_cmd(cmd, env);
	}
	else
	{
		waitpid(id_cmd, NULL, 0);
		close(fd_pipe[1]);
		dup2(fd_pipe[0], 0);
	}
	return (0);
}

int	ft_here_doc(char *str)
{
	int		fd_out;
	char	*line;

	fd_out = ft_open_fd_out(str, 1);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
		{
			close (fd_out);
			return (-1);
		}
		if (ft_strncmp(line, str, ft_strlen(str)) == 0)
		{
			free (line);
			close (fd_out);
			return (0);
		}
		ft_putstr_fd(line, fd_out);
	}
}

int	ft_find_i(char **argv)
{
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		return (3);
	else
		return (2);
}

int	main(int argc, char **argv, char **env)
{
	int		fd_in_out[2];
	int		i;

	if (argc < 5)
		return (ft_error("Error : incorrect number of arguments\n"));
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		ft_here_doc(argv[2]);
		fd_in_out[1] = ft_open_fd_out(argv[argc - 1], 1);
	}
	else
		fd_in_out[1] = ft_open_fd_out(argv[argc - 1], 0);
	fd_in_out[0] = ft_find_fd_in(argv);
	if (fd_in_out[0] == -1 || fd_in_out[1] == -1)
		return (-1);
	if (dup2(fd_in_out[0], STDIN_FILENO) == -1)
		return (ft_error("Error : fd_in assignation failed\n"));
	i = ft_find_i(argv);
	while (i < argc - 2)
		exec_cmds(argv[i++], env);
	unlink(argv[2]);
	if (dup2(fd_in_out[1], STDOUT_FILENO) == -1)
		return (ft_error("Error : fd_out assignation failed\n"));
	exec_cmd(argv[argc - 2], env);
	close_2_fd(fd_in_out[0], fd_in_out[1]);
}
