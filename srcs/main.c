/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:26:14 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/19 21:50:38 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	/*
	char	**varenv;
	char	*line;

	varenv = ft_strsdup(env);
	line = ft_strdup("ceci est un test");
	ft_add_env_var(&varenv, line);
	ft_print_strs(varenv);
	(void) argc;
	(void) argv;
	*/
	
	t_var	var;

	(void) argc;
	(void) argv;
	// NB : a la fin on pourra rassembler toutes ces lignes dans une fonction ft_init_var, mais pour l'instant c'est plus lisible
	var.exit_nb = 0; //le code d'exit est initialise a 0 (l'ouverture de minishell s'est bien deroulee)
	var.env = ft_strsdup(env);
	//ft_print_strs(var.env);
	var.env = ft_modify_shlvl(var.env, 1);
	//ft_print_strs(var.env);
	ft_disable_echoctl();
	ft_set_sigquit_reception_handler();
	ft_set_sigint_reception_handler();
	var.line = readline(PROMPT);
	ft_parse_line(&var);
	
	while (var.line)
	{
		if (!ft_parse_line(&var))
			exit(EXIT_FAILURE);
		if (*(var.line))
			add_history(var.line);
		free(var.line);
		var.line = readline(PROMPT);
	}
	
	ft_print_info_list(var.token_list);
	ft_clear_and_free_all(var);
	exit(EXIT_SUCCESS);
}