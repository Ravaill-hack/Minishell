/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handle_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:14:52 by lmatkows          #+#    #+#             */
/*   Updated: 2025/03/12 09:29:18 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_read_while_heredoc(char *line, t_hdc hd, char *hdc, t_var *var)
{
	while (g_while_hd == 1)
	{
		(hd.i)++;
		line = readline("> ");
		if (!line || g_while_hd == 0)
		{
			ft_print_error_hdc(hd.i, hdc);
			break ;
		}
		if (ft_strncmp(line, hdc, ft_strlen(line)) == 0 || g_while_hd == 0)
		{
			free (line);
			break ;
		}
		ft_special_write(hd.fd, line, var);
		ft_putchar_fd('\n', hd.fd);
		free(line);
	}
	return (0);
}

int	ft_putdoll_fd(char *str, int i, int fd, t_var *var)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	len = 0;
	if (!str[i + 1] || ft_isspace(str[i + 1]) == 1 || str[i + 1] == '\"'
		|| str[i + 1] == '\'')
		tmp = ft_strdup("$");
	else if (str[i + 1] == '?' && (!str[2] || ft_isspace(str[i + 2]) == 1
			|| str[i + 2] == '\"' || str[i + 2] == '\''))
	{
		tmp = ft_itoa(var->exit_nb);
		len = 1;
	}
	else if (ft_doll_var_exists_hd(&(str[i + 1]), var->env))
	{
		tmp = ft_strdup(ft_extract_env_value_hd(var->env, &(str[i + 1])));
		while (str[i + len] && !ft_isspace(str[i + len + 1]) && str[i + len + 1] != '\"'
			&& str[i + len + 1] != '\'' && (str[i + len + 1] != '$' || len == 0))
			len ++;
	}
	else
		return (0);
	if (!tmp)
		return (0);
	ft_putstr_fd(tmp, fd);
	free (tmp);
	return (len);
}

void	ft_special_write(int fd, char *raw, t_var *var)
{
	int	i;

	i = 0;
	while (raw[i])
	{
		if (raw[i] != '$' || ft_is_in_squotes(raw, i) == 1)
			ft_putchar_fd(raw[i], fd);
		else
			i += ft_putdoll_fd(raw, i, fd, var);
		i++;
	}
}
