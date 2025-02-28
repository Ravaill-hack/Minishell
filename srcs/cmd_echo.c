/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:28:54 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/28 10:56:00 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_line_is_str(char *line)
{
	if (line && line[0] && line[0] != '-')
		return (1);
	return (0);
}

int	ft_is_valid_n(char *line)
{
	int	i;

	i = 2;
	if (line[0] != '-' || line[1] != 'n')
		return (0);
	if (line[2] == '\0')
		return (1);
	while (line[i] == 'n')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

int	ft_line_is_opt_n(char **chartab, int imax)
{
	int	i;
	int	n_saw;
	int	opt;

	i = 0;
	n_saw = 0;
	opt = 0;
	while (i <= imax)
	{
		if (ft_line_is_str(chartab[i]) == 1 && n_saw == 1)
			return (0);
		if (ft_is_valid_n(chartab[i]) == 1)
		{
			n_saw = 1;
			opt = 1;
		}
		i++;
	}
	return (opt);
}

int	ft_opt_n_enabled(char **chartab)
{
	int	i;

	i = 0;
	while (chartab[i])
	{
		if (ft_line_is_opt_n(chartab, i) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	ft_cmd_echo(t_cmd *cmd, t_var *var)
{
	int		i;
	int		opt;

	(void) var;
	i = 1;
	if (!cmd || !(cmd->arg) || !(cmd->arg[0]))
		return (FAILURE);
	opt = ft_opt_n_enabled(cmd->arg);
	if (cmd->arg[i])
	{
		while (cmd->arg[i])
		{
			if (ft_line_is_opt_n(cmd->arg, i) == 0)
				ft_putstr_fd(cmd->arg[i], 1);
			if (cmd->arg[i + 1])
				ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (opt == 0)
		ft_putchar_fd('\n', 1);
	return (SUCCESS);
}
