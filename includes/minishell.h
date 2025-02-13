/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:25:36 by lmatkows          #+#    #+#             */
/*   Updated: 2025/02/13 10:37:53 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# ifndef PROMPT
#  define PROMPT "minishell$ "
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/includes/libft.h"
# include "./libft/includes/get_next_line.h"
# include "./minitalk/includes/client/client.h"
# include "./minitalk/includes/server/server.h"

#endif