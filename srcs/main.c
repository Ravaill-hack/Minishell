/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:26:14 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/27 16:57:47 by juduchar         ###   ########.fr       */
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