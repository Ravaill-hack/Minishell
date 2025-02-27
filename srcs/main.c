/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:26:14 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/27 11:50:24 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_var	var;
	t_shell	*shell;
	char	*val;

	(void) argc;
	(void) argv;
	ft_init(&var, &shell, env);
	get_prompt(shell, &var);
	while (shell->prompt)
	{
		if (!ft_parse_line(&var, shell->prompt))
			ft_print_error_and_exit(var, *shell);
		if (*(var.token_list))
		{
			val = var.token_list[0]->val;
			if (ft_handle_cmd(&var, *shell, val) == FAILURE)
				ft_print_error();
			add_history(shell->prompt);
			ft_clear_and_free_while(*shell);
			ft_free_token_list(var.token_list);
		}
		get_prompt(shell, &var);
	}
	ft_clear_and_free_all(var, *shell);
	exit(EXIT_SUCCESS);
}
