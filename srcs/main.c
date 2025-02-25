/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:26:14 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/25 13:49:15 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_var	var;
	char	*val;
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		exit(EXIT_FAILURE);
	(void) argc;
	(void) argv;
	ft_init(&var, env);
	shell->terminal_prompt = "minishell$ ";
	get_prompt(shell, &var);
	while (shell->prompt)
	{
		if (!ft_parse_line(&var, shell->prompt))
			ft_print_error_and_exit(var);
		if (*(var.token_list))
		{
			val = var.token_list[0]->val;
			if (ft_handle_cmd(&var, val) == FAILURE)
				ft_print_error();
			add_history(shell->prompt);
			free(shell->prompt);
		}
		get_prompt(shell, &var);
	}
	ft_clear_and_free_all(var);
	exit(EXIT_SUCCESS);
}
