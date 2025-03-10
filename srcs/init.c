/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:26:01 by julien            #+#    #+#             */
/*   Updated: 2025/03/10 09:01:15 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DONE //

#include "minishell.h"

void	get_prompt(t_var *var, t_shell *shell)
{
	if (isatty(STDIN_FILENO) && VALGRIND_DEBUG == 0)
	{
		rl_attempted_completion_function = NULL;
		rl_inhibit_completion = 1;
		shell->prompt = readline(shell->terminal_prompt);
	}
	else
	{
		var->line = get_next_line(fileno(stdin));
		if (var->line)
		{
			shell->prompt = ft_strtrim(var->line, "\n");
			free(var->line);
		}
		else
			shell->prompt = NULL;
	}
}

int	ft_update_shlvl(char ***env, int level, t_var *var)
{
	int		shlvl;
	char	*new_shlvl;
	int		status;

	shlvl = ft_atoi(getenv("SHLVL"));
	if (!shlvl)
		return (FAILURE);
	var->shlvl0 = shlvl;
	new_shlvl = ft_itoa(shlvl + level);
	status = ft_update_env_var_value_from_key(env, "SHLVL",
			new_shlvl);
	return (free(new_shlvl), status);
}

t_shell	*ft_init_shell(void)
{
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		exit(EXIT_FAILURE);
	shell->terminal_prompt = ft_strdup("minishell$ ");
	shell->while_hdc = 0;
	return (shell);
}

char	**ft_create_empty_env(void)
{
	char	**env;
	char	*pwd;

	env = (char **)ft_calloc(4, sizeof(char *));
	if (!env)
		return (NULL);
	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	env[0] = ft_strjoin("PWD=", pwd);
	free(pwd);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = NULL;
	return (env);
}

void	ft_init(t_var *var, char **env)
{
	var->exit_nb = 0;
	if (env && (*env))
	{
		var->env = ft_strsdup(env);
		if (ft_update_shlvl(&var->env, 1, var) == FAILURE)
			exit(EXIT_FAILURE);
	}
	else
	{
		var->env = ft_create_empty_env();
		var->shlvl0 = 1;
		if (!var->env)
			exit(EXIT_FAILURE);
	}
	var->declare = NULL;
	ft_set_signals();
	rl_catch_signals = 0;
}
