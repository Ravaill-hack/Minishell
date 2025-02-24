/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:26:14 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/24 10:49:43 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_var	var;
	char	*val;

	(void) argc;
	(void) argv;
	printf("ok");
	ft_init(&var, env);
	var.line = readline(PROMPT);
	while (var.line)
	{
		if (!ft_parse_line(&var))
			ft_exit_error(var);
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
