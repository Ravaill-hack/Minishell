/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:35:39 by julien            #+#    #+#             */
/*   Updated: 2025/03/10 10:48:56 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_while_hd = 0;

int	main(int argc, char **argv, char **env)
{
	t_var	var;
	t_shell	*shell;
	int		status;

	(void) argc;
	(void) argv;
	status = SUCCESS;
	shell = ft_init_shell();
	var.token_list = NULL;
	ft_init(&var, env);
	get_prompt(&var, shell);
	while (shell->prompt)
	{
		var.exit_nb = ft_parse_line(&var, shell->prompt, shell);
		if (shell->prompt[0] && var.exit_nb == SUCCESS)
		{
			status = ft_handle_pipes(&var, shell);
			if (status != SUCCESS)
				var.exit_nb = status % 255;
			if (VALGRIND_DEBUG == 0)
				add_history(shell->prompt);
			ft_clear_and_free_while(&var, shell);
		}
		get_prompt(&var, shell);
	}
	ft_clear_and_free_all(&var, shell);
	exit(var.exit_nb);
}
