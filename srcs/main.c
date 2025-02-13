/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:26:14 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/13 15:56:57 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_get_env(char **env_shell)
{
	char	**env;
	int		i;

	i = 0;
	env = (char **)malloc(sizeof(char *));
	if (!env)
		return (NULL);
	while (env_shell[i])
	{
		env[i] = ft_strdup(env_shell[i]);

	}
}

t_minishell	*ft_init_var(char **env)
 {
	t_minishell	*var;

	var = (t_minishell *)malloc(sizeof(t_minishell));
	if (!var)
		return (NULL);
	var->env = ft_get_env(env);
	var->line = NULL;
	return (var);
 }

int	main(int argc, char **argv, char **env)
{
	t_minishell	*var;

	(void)argc;
	(void)argv;
	var = ft_init_var(env);
	while (1)
	{
		var->line = readline(PROMPT);
		add_history(var->line);
		//ft_error_line(var->line);
	}
	printf("%s\n", var->line);
	free (var->line);
}