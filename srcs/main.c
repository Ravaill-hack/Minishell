/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:26:14 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/18 10:28:14 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_var	var;

	(void) argc;
	(void) argv;
	var.env = ft_modify_shlvl(ft_chartab_dup(env), 1);
	ft_disable_echoctl();
	ft_set_sigquit_reception_handler();
	ft_set_sigint_reception_handler();
	var.line = readline(PROMPT);
	while (var.line)
	{
		ft_parse_line(&var);
		if (*(var.line))
			add_history(var.line);
		free(var.line);
		var.line = readline(PROMPT);
	}
	ft_clear_and_free_all(var);
	exit(EXIT_SUCCESS);
}