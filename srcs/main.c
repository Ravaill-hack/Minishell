/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:35:39 by julien            #+#    #+#             */
/*   Updated: 2025/03/12 14:01:40 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_while_hd = 0;

int	main(int argc, char **argv, char **env)
{
	t_var	var;
	t_shell	*shell;

	(void) argc;
	(void) argv;
	var.status = SUCCESS;
	shell = ft_init_shell();
	ft_init(&var, env);
	get_prompt(&var, shell);
	while (shell->prompt)
	{
		var.status = ft_parse_line(&var, shell->prompt, shell);
		if (shell->prompt[0] && var.status == SUCCESS && var.is_empt_line == 0)
		{
			var.status = ft_handle_pipes(&var, shell);
			if (var.status != SUCCESS)
				var.exit_nb = var.status % 255;
			if (VALGRIND_DEBUG == 0)
				add_history(shell->prompt);
			ft_clear_and_free_while(&var, shell);
		}
		get_prompt(&var, shell);
	}
	ft_clear_and_free_all(&var, shell);
	exit(var.exit_nb);
}
