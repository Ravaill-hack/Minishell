/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:26:14 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/18 14:26:28 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_var	var;

	(void) argc;
	(void) argv;
	var.env = ft_strsdup(env);
	//ft_print_strs(var.env);
	var.env = ft_modify_shlvl(var.env, 1);
	//ft_print_strs(var.env);
	ft_disable_echoctl();
	ft_set_sigquit_reception_handler();
	ft_set_sigint_reception_handler();
	var.line = readline(PROMPT);
	while (var.line)
	{
		if (!ft_parse_line(&var))
			exit(EXIT_FAILURE);
		if (*(var.line))
			add_history(var.line);
		ft_free_line(var);
		var.line = readline(PROMPT);
	}
	ft_clear_and_free_all(var);
	exit(EXIT_SUCCESS);
}