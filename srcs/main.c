/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:35:39 by julien            #+#    #+#             */
/*   Updated: 2025/03/04 19:18:54 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_var	var;
	t_shell	*shell;

	(void) argc;
	(void) argv;
	shell = ft_init_shell();
	var.token_list = NULL;
	ft_init(&var, env);
	get_prompt(&var, shell);
	while (shell->prompt)
	{
			//ft_print_error_and_exit(var, *shell);
		if (ft_parse_line(&var, shell->prompt) != FAILURE)
		{
			//ft_print_info_list(*(var.token_list), var.env);
			//ft_print_info_cmd_list(var.nb_cmd, var.cmd);
			if (ft_handle_pipes(&var, *shell) == FAILURE)
				ft_print_error();
			if (VALGRIND_DEBUG == 0)
				add_history(shell->prompt);
			ft_clear_and_free_while(&var, shell);
		}
		get_prompt(&var, shell);
	}
	ft_clear_and_free_all(&var, shell);
	exit(EXIT_SUCCESS);
}

// FOR MISHELL TESTER 2
// /!\ DOESN'T WORK FOR NOW
// TO DO : ADD EXIT STATUS BEFORE
/*
int	ft_launch_minishell(char *line, char **env)
{
	t_var	var;
	t_shell	*shell;
	char	*val;

	ft_init(&var, &shell, env);
	shell->prompt = line;
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
		shell->prompt = line;
	}
	ft_clear_and_free_all(var, *shell);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		int exit_status = ft_launch_minishell(argv[2], env);
		exit(exit_status);
	}
}
*/