/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:35:39 by julien            #+#    #+#             */
/*   Updated: 2025/03/14 12:29:45 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_while_hd = 0;

void	ft_add_history_and_clear(t_shell *shell, t_var *var)
{
	if (VALGRIND_DEBUG == 0)
		add_history(shell->prompt);
	if (shell->prompt)
	{
		free(shell->prompt);
		shell->prompt = NULL;
	}
	if (var->token_list)
	{
		ft_free_token_list(var->token_list);
		free(var->token_list);
		var->token_list = NULL;
	}
	if (var->cmd)
		ft_free_cmd_list(var->cmd);
	if (var->fd_pipe)
		ft_free_array2d(var->fd_pipe);
	
}

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
		if (shell->prompt[0] && var.status == SUCCESS && var.is_empty_line == 0)
		{
			//ft_print_info_list(*var.token_list, var.env);
			//ft_print_info_cmd_list(var.nb_cmd, var.cmd);
			var.status = ft_handle_pipes(&var, shell);
			var.exit_nb = var.status % 255;
			if (isatty(STDIN_FILENO) && VALGRIND_DEBUG == 0)
				add_history(shell->prompt);
			ft_clear_and_free_while(&var, shell);
		}
		get_prompt(&var, shell);
	}
	ft_clear_and_free_all(&var, shell);
	exit(var.exit_nb);
}
