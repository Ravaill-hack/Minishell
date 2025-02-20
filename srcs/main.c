/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:26:14 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/20 22:05:27 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_var	var;
	(void) argc;
	(void) argv;
	if (!(isatty(STDIN_FILENO)))
		exit(EXIT_FAILURE);
	var.exit_nb = 0;
	var.env = ft_strsdup(env);
	if (!var.env)
		exit(EXIT_FAILURE);
	var.env = ft_modify_shlvl(var.env, 1);
	if (!var.env)
		exit(EXIT_FAILURE);
	ft_disable_echoctl();
	ft_set_sigquit_reception_handler();
	ft_set_sigint_reception_handler();
	var.line = readline(PROMPT);
	ft_parse_line(&var);
	//ft_print_info_list(*(var.token_list));
	while (var.line)
	{
		if (!ft_parse_line(&var))
		{
			ft_putstr_fd("Error\n", 2);
			ft_clear_and_free_all(var);
			exit(EXIT_FAILURE);
		}
		if (*(var.token_list))
		{
			if (ft_strncmp(var.token_list[0]->val, "exit", ft_strlen(var.token_list[0]->val)) == 0)
			{
				if (ft_cmd_exit(var, var.env, *(var.token_list)) == FAILURE)
				{
					ft_putstr_fd("Error\n", 2);
					ft_clear_and_free_all(var);
					exit(EXIT_FAILURE);
				}
			}
			if (ft_strncmp(var.token_list[0]->val, "env", ft_strlen(var.token_list[0]->val)) == 0)
				ft_cmd_env(var.env, *(var.token_list));
			if (ft_strncmp(var.token_list[0]->val, "unset", 5) == 0)
			{
				if (ft_cmd_unset(&var.env, *(var.token_list)) == FAILURE)
					ft_putstr_fd("Error\n", 2);
			}
			if (ft_strncmp(var.token_list[0]->val, "export", 6) == 0)
			{
				if (ft_cmd_export(&var.env, *(var.token_list)) == FAILURE)
					ft_putstr_fd("Error\n", 2);
			}
			if (ft_strncmp(var.token_list[0]->val, "pwd", ft_strlen(var.token_list[0]->val)) == 0)
			{
				if (ft_cmd_pwd(var.env, *(var.token_list)) == FAILURE)
					ft_putstr_fd("Error\n", 2);
			}
			/*if (ft_strncmp(var.token_list[0]->val, "cd", 2) == 0)
			{
				if (ft_cmd_cd(&var.env, *(var.token_list)) == FAILURE)
					ft_putstr_fd("Error\n", 2);
			}
			if (ft_strncmp(var.token_list[0]->val, "echo", 4) == 0)
			{
				if (ft_cmd_echo(var.env, *(var.token_list)) == FAILURE)
					ft_putstr_fd("Error\n", 2);
			}*/

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
		free(var.line);
		}
		var.line = readline(PROMPT);
	}
	//ft_print_info_list(var.token_list);
	ft_clear_and_free_all(var);
	exit(EXIT_SUCCESS);
}