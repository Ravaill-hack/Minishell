/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:26:14 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/21 15:08:54 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init(t_var *var, char **env)
{
	if (!(isatty(STDIN_FILENO)))
		exit(EXIT_FAILURE);
	var->exit_nb = 0;
	var->env = ft_strsdup(env);
	if (!var->env)
		exit(EXIT_FAILURE);
	var->env = ft_modify_shlvl(var->env, 1);
	if (!var->env)
		exit(EXIT_FAILURE);
	ft_disable_echoctl();
	ft_set_sigquit_reception_handler();
	ft_set_sigint_reception_handler();
}

int	main(int argc, char **argv, char **env)
{
	t_var	var;
	char	*val;

	(void) argc;
	(void) argv;
	ft_init(&var, env);
	var.line = readline(PROMPT);
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
			val = var.token_list[0]->val;
			if (ft_strncmp(val, "exit", ft_strlen(val)) == 0)
			{
				if (ft_cmd_exit(var, var.env, *(var.token_list)) == FAILURE)
				{
					ft_putstr_fd("Error\n", 2);
					ft_clear_and_free_all(var);
					exit(EXIT_FAILURE);
				}
			}
			if (ft_strncmp(val, "env", ft_strlen(val)) == 0)
				ft_cmd_env(var.env, *(var.token_list));
			if (ft_strncmp(val, "unset", 5) == 0)
			{
				if (ft_cmd_unset(&var.env, *(var.token_list)) == FAILURE)
					ft_putstr_fd("Error\n", 2);
			}
			if (ft_strncmp(val, "export", 6) == 0)
			{
				if (ft_cmd_export(&var.env, *(var.token_list)) == FAILURE)
					ft_putstr_fd("Error\n", 2);
			}
			if (ft_strncmp(val, "pwd", ft_strlen(val)) == 0)
			{
				if (ft_cmd_pwd(var.env, *(var.token_list)) == FAILURE)
					ft_putstr_fd("Error\n", 2);
			}
			if (ft_strncmp(val, "cd", 2) == 0)
			{
				if (ft_cmd_cd(var.env, *(var.token_list)) == FAILURE)
					ft_putstr_fd("Error\n", 2);
			}
			if (ft_strncmp(val, "echo", 4) == 0)
			{
				if (ft_cmd_echo(*(var.token_list)) == FAILURE)
					ft_putstr_fd("Error\n", 2);
			}
			add_history(var.line);
			free(var.line);
		}
		var.line = readline(PROMPT);
	}
	ft_clear_and_free_all(var);
	exit(EXIT_SUCCESS);
}
