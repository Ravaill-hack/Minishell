/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juduchar <juduchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:26:01 by julien            #+#    #+#             */
/*   Updated: 2025/03/06 11:28:09 by juduchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_prompt(t_var *var, t_shell *shell)
{
	if (isatty(STDIN_FILENO) && VALGRIND_DEBUG == 0)
		shell->prompt = readline(shell->terminal_prompt);
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

int	ft_update_shlvl(char ***env, int level)
{
	int		shlvl;
	char	*new_shlvl;
	int		status;

	shlvl = ft_atoi(getenv("SHLVL"));
	if (!shlvl)
		return (FAILURE);
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

void	ft_init(t_var *var, char **env)
{
	var->exit_nb = 0;
	var->env = ft_strsdup(env);
	if (!var->env)
		exit(EXIT_FAILURE);
	if (ft_update_shlvl(&var->env, 1) == FAILURE)
		exit(EXIT_FAILURE);
	ft_disable_echoctl();
	ft_set_sigint_sigquit_parent();
}
