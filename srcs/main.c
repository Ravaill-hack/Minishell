/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:26:14 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/19 17:59:16 by juduchar         ###   ########.fr       */
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
		{
			if (ft_strncmp(var.token_list[0][0].val, "exit", ft_strlen(var.token_list[0][0].val)) == 0)
			{
				if (ft_cmd_exit(var) == FAILURE)
				{
					ft_putstr_fd("Error\n", 2);
					ft_clear_and_free_all(var);
					exit(EXIT_FAILURE);
				}
			}
			if (ft_strncmp(var.token_list[0][0].val, "env", ft_strlen(var.token_list[0][0].val)) == 0)
				ft_cmd_env(var);
			if (ft_strncmp(var.token_list[0][0].val, "unset", ft_strlen(var.token_list[0][0].val)) == 0)
			{
				if (ft_cmd_unset(&var) == FAILURE)
					ft_putstr_fd("Error\n", 2);
			}
			if (ft_strncmp(var.token_list[0][0].val, "export", ft_strlen(var.token_list[0][0].val)) == 0)
				ft_cmd_export(&var);
					// if first token is pwd
					// and only if pwd is alone on the line
					// print the value of PWD in env
					
					// if first token is echo
					// and if echo is alone on the line
					// ???
					
					// check if the next token is the option -n
					// if echo is followed by a string without quotes
					// print this string (without \n if -n)
					// /!\ if there is a $var
					// replace $var with the value of var in env
					// if
			// and only if exit is alone on the line (?)			
			// SHLVL--
			// if SHLVL == getent("SHLVL")
			// clear and free all
			// exit
			// if first token is env
			// and only if env is alone on the line (?)
			// print env
			
			// if first token is unset
			// and next token is an env var
			// that is present in env
			// remove it from env

			// if first token is export
			// three cases :
			// if there is not next token
			// print env but with "declare -x" before each line
			// (use the same function as for env, but with a flag ?)
			// if there is a next token
			// split with = (key=value)
			// if the key is an env var
			// that is not present in env
			// add this value to env
			// if key is an env var
			// that is present in env
			// update this value in env
			// /!\ with a value of $var
			// replace $var with the value of var in env
			// example : export PATH=$PATH:/chemin/test
			// check if the value after $ in uppercase is an env var
			// take the value of this env var
			// concatenate with the string after this env var
			// and replace the env var with this new string

			// if first token is pwd
			// and only if pwd is alone on the line (?)
			// print the value of PWD in env

			// if first token is echo
			// and if echo is alone on the line
			// ???

			// check if the next token is the option -n
			// if echo is followed by a string without quotes			
			// print this string (without \n if -n)
			// /!\ if there is a $var
			// replace $var with the value of var in env
			// if echo is followed by a string with double quotes
			// same as above
			// if echo is followed by a string with single quotes
			// same as above but without replacing $var
			// /!\ check if the quotes are closed !
			// if not, return an error message
			
			// if first token is cd
			// NOTE : don't forget to update PWD in env for each case
			// and if cd is alone on the line
			// cd to the home directory
			// if the second token is ~
			// and there is no third token
			// idem
			// if the second token is /
			// cd to the root directory
			// . is the current directory
			// .. is the parent directory
			add_history(var.line);
		}
		ft_free_line(var);
		var.line = readline(PROMPT);
	}
	ft_clear_and_free_all(var);
	exit(EXIT_SUCCESS);
}