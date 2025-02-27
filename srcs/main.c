/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:26:14 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/27 09:12:07 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_var	var;
	char	*val;

	(void) argc;
	(void) argv;
	ft_init(&var, env);
	var.line = readline(PROMPT);
	while (var.line)
	{
		if (!ft_parse_line(&var))
			ft_exit_error(var);
		ft_print_info_list(*(var.token_list), var.env);
		//ft_print_info_cmd_list(var.nb_cmd, var.cmd);
		if (*(var.token_list))
		{
			val = var.token_list[0]->val;
			if (ft_handle_cmd(&var, val) == FAILURE)
				ft_exit_error(var);
			add_history(var.line);
			free(var.line);
		}
		var.line = readline(PROMPT);
	}
	ft_clear_and_free_all(var);
	exit(EXIT_SUCCESS);
}
