/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:26:14 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/18 17:29:18 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_var	var;

	(void) argc;
	(void) argv;
	// NB : a la fin on pourra rassembler toutes ces lignes dans une fonction ft_init_var, mais pour l'instant c'est plus lisible
	
	// var.shlvl_0 = ft_atoi(&env[ft_get_line_env(env, "SHLVL=")][6]); //garde en memoire le niveau de shell au moment du demarrage
	// ft_putnbr_fd(var.shlvl_0, 1);
	
	// ou utiliser getenv plutot que ft_get_line_env pour eviter de parcourir l'env a chaque fois
	// printf("%s", getenv("SHLVL"));

	// si l'entree standard n'est pas un terminal, on quitte
	if (!(isatty(STDIN_FILENO)))
		exit(EXIT_FAILURE);
	var.exit_nb = 0; // le code d'exit est initialise a 0 (l'ouverture de minishell s'est bien deroulee)
	var.env = ft_strsdup(env);
	// si l'allocation de memoire a echoue ou que l'env est vide, on quitte
	if (!var.env)
		exit(EXIT_FAILURE);
	//ft_print_strs(var.env);
	var.env = ft_modify_shlvl(var.env, 1);
	//ft_print_strs(var.env);
	ft_disable_echoctl();
	ft_set_sigquit_reception_handler();
	ft_set_sigint_reception_handler();
	var.line = readline(PROMPT);
	while (var.line)
	{
		if (!ft_parse_line(&var))
		{
			ft_putstr_fd("Error\n", 2);
			ft_clear_and_free_all(var);
			exit(EXIT_FAILURE);
		}
		if (*(var.line))
			add_history(var.line);
		ft_free_line(var);
		var.line = readline(PROMPT);
	}
	ft_clear_and_free_all(var);
	exit(EXIT_SUCCESS);
}